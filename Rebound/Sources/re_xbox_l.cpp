#include "re_xbox_l.h"
#include <string.h>


ReXboxL *th_this;
QString  th_keycode;
int      th_keyval;

#define JOYSTICK_DELAY 100

ReXboxL::ReXboxL(QObject *item, int native, QObject *parent) : QObject(parent)
{
    //init
    ui = item;
    charBuffer = '0';
    isBufferEmpty = true;
    commandMode = false;
    isNative = native;


    if (native)
    {
        th_this = this;

        createProcess(QString::number(native));

        //key_thread = new std::thread(KeyParser_main);
    }
    else
    {
        client = new ReClient(ui);
        connect(client, SIGNAL(newKey(QString)), this, SLOT(keyTcpRead(QString)));
    }
}

void ReXboxL::keyTcpRead(QString key)
{
    if( key=="a" )
    {
        emit buttonAPressed();
    }
    else if( key=="b" )
    {
        emit buttonBPressed();
    }
    else if( key=="c" )
    {
        //emit buttonCenterPressed();
    }
    else if( key=="d" )
    {
        emit buttonDownPressed();
    }
    else if( key=="e" ) //Left Axis
    {
        emit buttonLAxisRight();
    }
    else if( key=="f" ) //Left Axis
    {
        emit buttonLAxisLeft();
    }
    else if( key=="g" )
    {
        emit buttonGuidePressed();
    }
    else if( key=="h" ) //Left Axis
    {
        emit buttonLAxisUp();
    }
    else if( key=="i" ) //Left Axis
    {
        emit buttonLAxisDown();
    }
    else if( key=="j" ) //Right Axis
    {
        emit buttonRAxisRight();
    }
    else if( key=="k" ) //Right Axis
    {
        emit buttonRAxisLeft();
    }
    else if( key=="l" )
    {
        emit buttonLeftPressed();
    }
    else if( key=="m" )
    {
        if( isUiVisible(ui) )
        {
             client->sendData("M", 1);
             hideUI(ui);
        }
        else
        {
            emit buttonStartPressed();
        }
    }
    else if( key=="n" ) //Right Axis
    {
        emit buttonRAxisUp();
    }
    else if( key=="o" ) //Right Axis
    {
        emit buttonRAxisDown();
    }
    else if( key=="l1" )
    {
        emit buttonL1Pressed();
    }
    else if( key=="l2" )
    {
        emit buttonL2Pressed();
    }
    else if( key=="l3" )
    {
        //emit buttonL3Pressed();
    }
    else if( key=="r" )
    {
        emit buttonRightPressed();
    }
    else if( key=="r1" )
    {
        emit buttonR1Pressed();
    }
    else if( key=="r2" )
    {
        emit buttonR2Pressed();
    }
    else if( key=="r3" )
    {
        ///FIXME
        //emit buttonR3Pressed();
    }
    else if( key=="s" )
    {
        emit buttonSelectPressed(); // not native
    }
    else if( key=="u" )
    {
        emit buttonUpPressed();
    }
    else if( key=="x" )
    {
        emit buttonXPressed();
    }
    else if( key=="y" )
    {
        emit buttonYPressed();
    }
    else
    {
        qDebug() << "Unkdown packet:" << key << key.size();
    }
}

void ReXboxL::createProcess(QString evnum)
{
    QString cmd_arg = "/dev/input/event" + evnum;

    qDebug() << cmd_arg;

    QString program = "evtest";
    QStringList arguments;
    arguments << cmd_arg;

    ev_process = new QProcess(this);
    connect(ev_process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyData()));

    ev_process->start(program, arguments);
}

void ReXboxL::readyData()
{
    QString data = ev_process->readAllStandardOutput();
    QStringList lines = data.split('\n');

//    qDebug() << lines.size();
    for ( int i=0 ; i<lines.size() ; i++ )
    {
        QString line = lines[i];
        qDebug() << line;

        QStringList space_separated;
        if( line.contains("type 1") || line.contains("type 3"))
        {
            space_separated = line.split(" ");

            if( space_separated.count()>10 )
            {
                QString key_code = space_separated[8];
                QString key_val = space_separated[10];

                //clean string
                key_code.chop(2);
                key_code.remove(0, 1);

                int key_val_int = key_val.toInt();
                keyParser(key_code, key_val_int);
            }
        }
    }
}

void keyHandler(int sig)
{
    th_this->keyParser(th_keycode, th_keyval);
}

void KeyParser_main()
{
    char   buf_a[1024];
    size_t max_len = 1024;
    char  *buffer = buf_a; //need for POSIX?!

    pthread_t intf_thread = pthread_self();

    // sigaction used for sending data on tcp when data received
    // from high level
    struct sigaction key_action;
    key_action.sa_handler = keyHandler;
    key_action.sa_flags = SA_RESTART;
    sigaction(RE_SIG_KEY, &key_action, NULL);

    while( 1 )
    {
//        getline(&buffer, &max_len, stdin);
        if (!fgets(buf_a, sizeof(buf_a), stdin))
        {
            continue;
        }

        QString line = QString(buffer);
//        qDebug();

        QStringList space_separated;
        if( line.contains("type 1") || line.contains("type 3"))
        {
            space_separated = line.split(" ");

            if( space_separated.count()>10 )
            {
                th_keycode = space_separated[8];
                QString key_val = space_separated[10];

                //clean string
                th_keycode.chop(2);
                th_keycode.remove(0, 1);

                th_keyval = key_val.toInt();
                pthread_kill(intf_thread, RE_SIG_KEY);
            }
        }
    }
}

void ReXboxL::keyParser(QString key, int value)
{
    qDebug() << key << value;
    if( key==RE_KEY_HOMEPAGE )
    {
        buttonGuideChanged(value);
    }
    else if( key==RE_KEY_SOUTH )
    {
        buttonAChanged(value);
    }
    else if( key==RE_KEY_EAST )
    {
        buttonBChanged(value);
    }
    else if( key==RE_KEY_NORTH )
    {
        buttonXChanged(value);
    }
    else if( key==RE_KEY_WEST )
    {
        buttonYChanged(value);
    }
    else if( key==RE_KEY_START )
    {
        buttonStartChanged(value);
    }
    else if( key==RE_KEY_BACK )
    {
        buttonSelectChanged(value);
    }
    else if( key==RE_KEY_HAT0Y )
    {
        if( value==1 )
        {
            buttonDownChanged(1);
        }
        else if( value==-1 )
        {
            buttonUpChanged(1);
        }
        else if( value==0 )
        {
            buttonDownChanged(0);
            buttonUpChanged(0);
        }
    }
    else if( key==RE_KEY_HAT0X )
    {
        if( value==1 )
        {
            buttonRightChanged(1);
        }
        else if( value==-1 )
        {
            buttonLeftChanged(1);
        }
        else if( value==0 )
        {
            buttonRightChanged(0);
            buttonLeftChanged(0);
        }
    }
    else if( key==RE_KEY_TR )
    {
        buttonR1Changed(value);
    }
    else if( key==RE_KEY_TL )
    {
        buttonL1Changed(value);
    }
    else if( key==RE_KEY_GAS )
    {
        buttonR2Changed(value/1023.0);
    }
    else if( key==RE_KEY_BRAKE )
    {
        buttonL2Changed(value/1023.0);
    }
    else if( key==RE_KEY_THUMBR )
    {
        buttonR3Changed(value);
    }
    else if( key==RE_KEY_THUMBL )
    {
        buttonL3Changed(value);
    }
    else if( key==RE_KEY_X )
    {
        buttonAxisLxChanged(value/65530.0);
    }
    else if( key==RE_KEY_Y )
    {
        buttonAxisLyChanged(value/65530.0);
    }
    else if( key==RE_KEY_Z )
    {
        buttonAxisRxChanged(value/65530.0);
    }
    else if( key==RE_KEY_RZ )
    {
        buttonAxisRyChanged(value/65530.0);
    }
}

ReXboxL::~ReXboxL()
{
    qDebug() << "Closing Server";
}

void ReXboxL::buttonAChanged(bool value)
{
    qDebug() << "A Pressed";
    if ( value==1 )
    {
        emit buttonAPressed();
    }
}

void ReXboxL::buttonBChanged(bool value)
{
    if ( value==1 )
    {
        emit buttonBPressed();
    }
}

void ReXboxL::buttonXChanged(bool value)
{
    if ( value==1 )
    {
        emit buttonXPressed();
    }
}

void ReXboxL::buttonYChanged(bool value)
{
    if ( value==1 )
    {
        emit buttonYPressed();
    }
}

void ReXboxL::buttonL1Changed(bool value)
{
    if ( value==1 )
    {
        emit buttonL1Pressed();
    }
}

void ReXboxL::buttonL2Changed(double value)
{
    if ( value==1 )
    {
        emit buttonL2Pressed();
    }
}

void ReXboxL::buttonL3Changed(bool value)
{
    qDebug() << "l3 pressed";
    if ( value==1 )
    {
        //emit buttonL3Pressed();
    }
}

void ReXboxL::buttonR1Changed(bool value)
{
    if ( value==1 )
    {
        emit buttonR1Pressed();
    }
}

void ReXboxL::buttonR2Changed(double value)
{
    qDebug() << "r2 pressed";
    if ( value==1 )
    {
        emit buttonR2Pressed();
    }
}

void ReXboxL::buttonR3Changed(bool value)
{
    qDebug() << "r3 pressed";
    if ( value==1 )
    {
        //emit buttonR3Pressed();
    }
}

void ReXboxL::buttonAxisLxChanged(double value)
{
    if( last_la_x==0 )
    {
        if( value<0.02 )
        {
            last_la_x = 1;
            emit buttonLAxisRight();
        }
        else if( value>0.98  )
        {
            last_la_x = 1;
            emit buttonLAxisLeft();
        }
    }
    else if( value<0.5 && value>0.25 )
    {
        last_la_x = 0;
    }
}

void ReXboxL::buttonAxisLyChanged(double value)
{
    if( last_la_y==0 )
    {
        if( value<0.02 ) //up
        {
            last_la_y = 1;
            emit buttonLAxisUp();
        }
        else if( value>0.98 ) //down
        {
            last_la_y = 1;
            emit buttonLAxisDown();
        }
    }
    else if( value<0.75 && value>0.25 )
    {
        last_la_y = 0;
    }
}

void ReXboxL::buttonAxisRxChanged(double value)
{
    if( last_la_x==0 )
    {
        if( value<0.02 )
        {
            last_la_x = 1;
            emit buttonRAxisRight();
        }
        else if( value>0.98 )
        {
            last_la_x = 1;
            emit buttonRAxisLeft();
        }
    }
    else if( value<0.75 && value>0.25 )
    {
        last_la_x = 0;
    }
}

void ReXboxL::buttonAxisRyChanged(double value)
{
//    qDebug() << value;
    if( last_ra_y==0 )
    {
        if( value<0.02 ) //up
        {
            last_ra_y = 1;
            emit buttonRAxisUp();
        }
        else if( value>0.98 ) //down
        {
            last_ra_y = 1;
            emit buttonRAxisDown();
        }
    }
    else if( value<0.75 && value>0.25 )
    {
        last_ra_y = 0;
    }
}

void ReXboxL::buttonStartChanged(bool value)
{
    if ( value==0 )
    {
        emit buttonStartPressed();
    }
}

void ReXboxL::buttonSelectChanged(bool value)
{
    if ( value==0 )
    {
        emit buttonSelectPressed();
    }
}

void ReXboxL::buttonCenterChanged(bool value)
{
    if ( value==0 )
    {
        qDebug() << "Center pressed";
        //emit buttonCenterPressed();
    }
}

void ReXboxL::buttonGuideChanged(bool value)
{
    qDebug() << "Guide pressed";
    if ( value==1 )
    {
        emit buttonGuidePressed();
    }
}

void ReXboxL::buttonLeftChanged(bool value)
{
    if ( value==1 )
    {
        emit buttonLeftPressed();
    }
}

void ReXboxL::buttonRightChanged(bool value)
{
    if ( value==1 )
    {
        emit buttonRightPressed();
    }
}

void ReXboxL::buttonUpChanged(bool value)
{
    if ( value==1 )
    {
        emit buttonUpPressed();
    }
}

void ReXboxL::buttonDownChanged(bool value)
{
    if ( value==1 )
    {
        emit buttonDownPressed();
    }
}
