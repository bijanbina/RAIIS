#include "re_native.h"
#include <string.h>

#define JOYSTICK_DELAY 100

ReNative::ReNative(QObject *parent) : QObject(parent)
{
    //init
    charBuffer = '0';
    isBufferEmpty = true;
    commandMode=false;

    pad = new QGamepad;
    connect(pad, SIGNAL(buttonAChanged(bool)),
            this, SLOT(buttonAChanged(bool)));
    connect(pad, SIGNAL(buttonBChanged(bool)),
            this, SLOT(buttonBChanged(bool)));
    connect(pad, SIGNAL(buttonXChanged(bool)),
            this, SLOT(buttonXChanged(bool)));
    connect(pad, SIGNAL(buttonYChanged(bool)),
            this, SLOT(buttonYChanged(bool)));

    connect(pad, SIGNAL(buttonL1Changed(bool)),
            this, SLOT(buttonL1Changed(bool)));
    connect(pad, SIGNAL(buttonL2Changed(double)),
            this, SLOT(buttonL2Changed(double)));
    connect(pad, SIGNAL(buttonL3Changed(bool)),
            this, SLOT(buttonL3Changed(bool)));
    connect(pad, SIGNAL(buttonR1Changed(bool)),
            this, SLOT(buttonR1Changed(bool)));
    connect(pad, SIGNAL(buttonR2Changed(double)),
            this, SLOT(buttonR2Changed(double)));
    connect(pad, SIGNAL(buttonR3Changed(bool)),
            this, SLOT(buttonR3Changed(bool)));

    connect(pad, SIGNAL(axisLeftXChanged(double)),
            this, SLOT(buttonAxisLxChanged(double)));
    connect(pad, SIGNAL(axisLeftYChanged(double)),
            this, SLOT(buttonAxisLyChanged(double)));
    connect(pad, SIGNAL(axisRightXChanged(double)),
            this, SLOT(buttonAxisRxChanged(double)));
    connect(pad, SIGNAL(axisRightYChanged(double)),
            this, SLOT(buttonAxisRyChanged(double)));

    connect(pad, SIGNAL(buttonStartChanged(bool)),
            this, SLOT(buttonStartChanged(bool)));
    connect(pad, SIGNAL(buttonSelectChanged(bool)),
            this, SLOT(buttonSelectChanged(bool)));
    connect(pad, SIGNAL(buttonCenterChanged(bool)),
            this, SLOT(buttonCenterChanged(bool)));
    connect(pad, SIGNAL(buttonGuideChanged(bool)),
            this, SLOT(buttonGuideChanged(bool)));

    connect(pad, SIGNAL(buttonLeftChanged(bool)),
            this, SLOT(buttonLeftChanged(bool)));
    connect(pad, SIGNAL(buttonRightChanged(bool)),
            this, SLOT(buttonRightChanged(bool)));
    connect(pad, SIGNAL(buttonUpChanged(bool)),
            this, SLOT(buttonUpChanged(bool)));
    connect(pad, SIGNAL(buttonDownChanged(bool)),
            this, SLOT(buttonDownChanged(bool)));
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

