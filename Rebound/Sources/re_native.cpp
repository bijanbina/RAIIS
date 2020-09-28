#include "re_native.h"
#include <string.h>

#define JOYSTICK_DELAY 100

ReNative::ReNative(QObject *item, QObject *parent) : QObject(parent)
{
    //init
    ui = item;
    charBuffer = '0';
    isBufferEmpty = true;
    commandMode = false;
    exec = new ReExec(ui);

    //read from stdin
    stdin_notify = new QSocketNotifier(STDIN_FILENO, QSocketNotifier::Read, this);
    connect(stdin_notify, SIGNAL(activated(int)), this, SLOT(readyData()));
    stdin_notify->setEnabled(true);

    stdin_file = new QFile;
    stdin_file->open(stdin, QIODevice::ReadOnly);
}

void ReNative::readyData()
{
    QString line = stdin_file->readLine();
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
            key_code.remove(0, 2);

            key_val.chop(1);

//                 qDebug() << key_code << key_val;

            int key_val_int = key_val.toInt();
            keyParser(key_code, key_val_int);
        }
    }
}

void ReNative::keyParser(QString key, int value)
{
//    qDebug() << key << value;
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

ReNative::~ReNative()
{
    qDebug() << "Closing Server";
}

void ReNative::buttonAChanged(bool value)
{
    qDebug() << "A Pressed";
    if ( value==1 )
    {
        exec->buttonAPressed();
    }
}

void ReNative::buttonBChanged(bool value)
{
    if ( value==1 )
    {
        exec->buttonBPressed();
    }
}

void ReNative::buttonXChanged(bool value)
{
    if ( value==1 )
    {
        exec->buttonXPressed();
    }
}

void ReNative::buttonYChanged(bool value)
{
    if ( value==1 )
    {
        exec->buttonYPressed();
    }
}

void ReNative::buttonL1Changed(bool value)
{
    if ( value==1 )
    {
        exec->buttonL1Pressed();
    }
}

void ReNative::buttonL2Changed(double value)
{
    if ( value==1 )
    {
        exec->buttonL2Pressed();
    }
}

void ReNative::buttonL3Changed(bool value)
{
    qDebug() << "l3 pressed";
    if ( value==1 )
    {
        exec->buttonL3Pressed();
    }
}

void ReNative::buttonR1Changed(bool value)
{
    if ( value==1 )
    {
        exec->buttonR1Pressed();
    }
}

void ReNative::buttonR2Changed(double value)
{
    qDebug() << "r2 pressed";
    if ( value==1 )
    {
        exec->buttonR2Pressed();
    }
}

void ReNative::buttonR3Changed(bool value)
{
    qDebug() << "r3 pressed";
    if ( value==1 )
    {
        exec->buttonR3Pressed();
    }
}

void ReNative::buttonAxisLxChanged(double value)
{
    if( last_la_x==0 )
    {
        if( value<0.02 )
        {
            last_la_x = 1;
            exec->buttonLAxisRight();
        }
        else if( value>0.98  )
        {
            last_la_x = 1;
            exec->buttonLAxisLeft();
        }
    }
    else if( value<0.5 && value>0.25 )
    {
        last_la_x = 0;
    }
}

void ReNative::buttonAxisLyChanged(double value)
{
    if( last_la_y==0 )
    {
        if( value<0.02 ) //up
        {
            last_la_y = 1;
            exec->buttonLAxisUp();
        }
        else if( value>0.98 ) //down
        {
            last_la_y = 1;
            exec->buttonLAxisDown();
        }
    }
    else if( value<0.75 && value>0.25 )
    {
        last_la_y = 0;
    }
}

void ReNative::buttonAxisRxChanged(double value)
{
    if( last_la_x==0 )
    {
        if( value<0.02 )
        {
            last_la_x = 1;
            exec->buttonRAxisRight();
        }
        else if( value>0.98 )
        {
            last_la_x = 1;
            exec->buttonRAxisLeft();
        }
    }
    else if( value<0.75 && value>0.25 )
    {
        last_la_x = 0;
    }
}

void ReNative::buttonAxisRyChanged(double value)
{
//    qDebug() << value;
    if( last_ra_y==0 )
    {
        if( value<0.02 ) //up
        {
            last_ra_y = 1;
            exec->buttonRAxisUp();
        }
        else if( value>0.98 ) //down
        {
            last_ra_y = 1;
            exec->buttonRAxisDown();
        }
    }
    else if( value<0.75 && value>0.25 )
    {
        last_ra_y = 0;
    }
}

void ReNative::buttonStartChanged(bool value)
{
    if ( value==1 )
    {
        exec->buttonStartChanged();
    }
}

void ReNative::buttonSelectChanged(bool value)
{
    if ( value==1 )
    {
        exec->buttonSelectChanged(1);
    }
}

void ReNative::buttonCenterChanged(bool value)
{
    if ( value==1 )
    {
        qDebug() << "Center pressed";
        exec->buttonCenterChanged();
    }
}

void ReNative::buttonGuideChanged(bool value)
{
    qDebug() << "Guide pressed";
    if ( value==1 )
    {
        exec->buttonGuideChanged();
    }
}

void ReNative::buttonLeftChanged(bool value)
{
    if ( value==1 )
    {
        exec->buttonLeftChanged();
    }
}

void ReNative::buttonRightChanged(bool value)
{
    if ( value==1 )
    {
        exec->buttonRightChanged();
    }
}

void ReNative::buttonUpChanged(bool value)
{
    if ( value==1 )
    {
        exec->buttonUpChanged();
    }
}

void ReNative::buttonDownChanged(bool value)
{
    if ( value==1 )
    {
        exec->buttonDownChanged();
    }
}

