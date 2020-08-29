#include "re_native.h"
#include <string.h>

#define JOYSTICK_DELAY 100

ReNative::ReNative(QObject *parent) : QObject(parent)
{
    //init
    charBuffer = '0';
    isBufferEmpty = true;
    commandMode=false;
}

void ReNative::loop()
{
    QFile in;
    in.open(stdin, QIODevice::ReadOnly);
    QStringList space_separated;

    while(true)
    {
         QString line = in.readLine();
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

                 qDebug() << key_code << key_val;

                 if( key_val==1 )
                 {

                 }

             }
         }
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
        exec.buttonAPressed();
    }
}

void ReNative::buttonBChanged(bool value)
{
    if ( value==1 )
    {
        exec.buttonBPressed();
    }
}

void ReNative::buttonXChanged(bool value)
{
    if ( value==1 )
    {
        exec.buttonXPressed();
    }
}

void ReNative::buttonYChanged(bool value)
{
    if ( value==1 )
    {
        exec.buttonYPressed();
    }
}

void ReNative::buttonL1Changed(bool value)
{
    if ( value==1 )
    {
        exec.buttonL1Pressed();
    }
}

void ReNative::buttonL2Changed(double value)
{
    if ( value==1 )
    {
        exec.buttonL2Pressed();
    }
}

void ReNative::buttonL3Changed(bool value)
{
    qDebug() << "l3 pressed";
    if ( value==1 )
    {
        exec.buttonL3Pressed();
    }
}

void ReNative::buttonR1Changed(bool value)
{
    if ( value==1 )
    {
        exec.buttonR1Pressed();
    }
}

void ReNative::buttonR2Changed(double value)
{
    qDebug() << "r2 pressed";
    if ( value==1 )
    {
        exec.buttonR2Pressed();
    }
}

void ReNative::buttonR3Changed(bool value)
{
    qDebug() << "r3 pressed";
    if ( value==1 )
    {
        exec.buttonR3Pressed();
    }
}

void ReNative::buttonAxisLxChanged(double value)
{
    if( last_la_x==0 )
    {
        if( value==1 )
        {
            last_la_x = 1;
            exec.buttonLAxisRight();
        }
        else if( value==-1 )
        {
            last_la_x = 1;
            exec.buttonLAxisLeft();
        }
    }
    else if( value<0.5 && value>-0.5 )
    {
        last_la_x = 0;
    }
}

void ReNative::buttonAxisLyChanged(double value)
{
    if( last_la_y==0 )
    {
        if( value<-0.99 ) //up
        {
            last_la_y = 1;
            exec.buttonLAxisUp();
        }
        else if( value>0.99 ) //down
        {
            last_la_y = 1;
            exec.buttonLAxisDown();
        }
    }
    else if( value<0.5 && value>-0.5 )
    {
        last_la_y = 0;
    }
}

void ReNative::buttonAxisRxChanged(double value)
{
    if( last_la_x==0 )
    {
        if( value==1 )
        {
            last_la_x = 1;
            exec.buttonRAxisRight();
        }
        else if( value==-1 )
        {
            last_la_x = 1;
            exec.buttonRAxisLeft();
        }
    }
    else if( value<0.5 && value>-0.5 )
    {
        last_la_x = 0;
    }
}

void ReNative::buttonAxisRyChanged(double value)
{
//    qDebug() << value;
    if( last_ra_y==0 )
    {
        if( value<-0.99 ) //up
        {
            last_ra_y = 1;
            exec.buttonRAxisUp();
        }
        else if( value>0.99 ) //down
        {
            last_ra_y = 1;
            exec.buttonRAxisDown();
        }
    }
    else if( value<0.5 && value>-0.5 )
    {
        last_ra_y = 0;
    }
}

void ReNative::buttonStartChanged(bool value)
{
    if ( value==1 )
    {
        exec.buttonStartChanged();
    }
}

void ReNative::buttonSelectChanged(bool value)
{
    if ( value==1 )
    {
        exec.buttonSelectChanged();
    }
}

void ReNative::buttonCenterChanged(bool value)
{
    if ( value==1 )
    {
        qDebug() << "Center pressed";
        exec.buttonCenterChanged();
    }
}

void ReNative::buttonGuideChanged(bool value)
{
    qDebug() << "Guide pressed";
    if ( value==1 )
    {
        exec.buttonGuideChanged();
    }
}

void ReNative::buttonLeftChanged(bool value)
{
    if ( value==1 )
    {
        exec.buttonLeftChanged();
    }
}

void ReNative::buttonRightChanged(bool value)
{
    if ( value==1 )
    {
        exec.buttonRightChanged();
    }
}

void ReNative::buttonUpChanged(bool value)
{
    if ( value==1 )
    {
        exec.buttonUpChanged();
    }
}

void ReNative::buttonDownChanged(bool value)
{
    if ( value==1 )
    {
        exec.buttonDownChanged();
    }
}

