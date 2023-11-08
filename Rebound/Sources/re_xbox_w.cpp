#include "re_xbox_w.h"

ReXboxW::ReXboxW(ReState *st, QObject *parent) : QObject(parent)
{
    state = st;
    tcp = new ReServer(state);
    admin = new ReAdminWin(7611);
    isNative = true;

#ifdef _WIN32
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
//    connect(pad, SIGNAL(buttonGuideChanged(bool)),
//            this, SLOT(buttonGuideChanged(bool)));

    connect(pad, SIGNAL(buttonLeftChanged(bool)),
            this, SLOT(buttonLeftChanged(bool)));
    connect(pad, SIGNAL(buttonRightChanged(bool)),
            this, SLOT(buttonRightChanged(bool)));
    connect(pad, SIGNAL(buttonUpChanged(bool)),
            this, SLOT(buttonUpChanged(bool)));
    connect(pad, SIGNAL(buttonDownChanged(bool)),
            this, SLOT(buttonDownChanged(bool)));

    //XBox Guide Button check
    backup = new ReXboxWin32;
    connect(backup, SIGNAL(buttonGuideChanged(bool)), SLOT(buttonGuideChanged(bool)));

    connect(tcp, SIGNAL(clientDisconnected()), this, SLOT(clientDisconnected()));
    connect(tcp, SIGNAL(clientConnected()), SLOT(clientConnected()));
    connect(tcp, SIGNAL(clientReqSusspend()), SLOT(clientReqSuspend()));

#endif

}

ReXboxW::~ReXboxW()
{
    delete tcp;
}

void ReXboxW::clientDisconnected()
{
    isNative = true;
}

void ReXboxW::clientConnected()
{
    isNative = false;
}

void ReXboxW::clientReqSuspend()
{
    emit requstSuspend();
}

void ReXboxW::buttonAChanged(bool value)
{
    if ( value==1 )
    {
        if(isNative)
        {
            emit buttonAPressed();
        }
        else
        {
            tcp->reboundSendKey("a",1);
        }
    }
}

void ReXboxW::buttonBChanged(bool value)
{
    if ( value==1 )
    {
        if(isNative)
        {
            emit buttonBPressed();
        }
        else
        {
            tcp->reboundSendKey("b",1);
        }
    }
}

void ReXboxW::buttonXChanged(bool value)
{
    if ( value==1 )
    {
        if(isNative)
        {
            emit buttonXPressed();
        }
        else
        {
            tcp->reboundSendKey("x",1);
        }
    }
}

void ReXboxW::buttonYChanged(bool value)
{
    if ( value==1 )
    {
        if(isNative)
        {
            emit buttonYPressed();
        }
        else
        {
            tcp->reboundSendKey("y",1);
        }
    }
}

void ReXboxW::buttonL1Changed(bool value)
{
    if ( value==1 )
    {
        if(isNative)
        {
            emit buttonL1Pressed();
        }
        else
        {
            tcp->reboundSendKey("l1",2);
        }
    }
}

void ReXboxW::buttonL2Changed(double value)
{
    if ( value==1 )
    {
        if(isNative)
        {
            emit buttonL2Pressed();
        }
        else
        {
            tcp->reboundSendKey("l2",2);
        }
    }
}

void ReXboxW::buttonL3Changed(bool value)
{
    if ( value==1 )
    {
        if(isNative)
        {
            ///FIXME
//            emit buttonL3Pressed();
        }
        else
        {
            tcp->reboundSendKey("l3",2);
        }
    }
}

void ReXboxW::buttonR1Changed(bool value)
{
    if ( value==1 )
    {
        if(isNative)
        {
            emit buttonR1Pressed();
        }
        else
        {
            tcp->reboundSendKey("r1",2);
        }
    }
}

void ReXboxW::buttonR2Changed(double value)
{
    if ( value==1 )
    {
        if(isNative)
        {
            emit buttonR2Pressed();
        }
        else
        {
            tcp->reboundSendKey("r2",2);
        }
    }
}

void ReXboxW::buttonR3Changed(bool value)
{
    if ( value==1 )
    {
        if(isNative)
        {
            ///FIXME
//            emit buttonR3Pressed();
        }
        else
        {
            tcp->reboundSendKey("r3",2);
        }
    }
}

void ReXboxW::buttonAxisLxChanged(double value)
{
    if( last_la_x==0 )
    {
        if( value==1 )
        {
            last_la_x = 1;
            if(isNative)
            {
                emit buttonLAxisRight();
            }
            else
            {
                tcp->reboundSendKey("e",1);
            }
        }
        else if( value==-1 )
        {
            last_la_x = 1;
            if(isNative)
            {
                emit buttonLAxisLeft();
            }
            else
            {
                tcp->reboundSendKey("f",1);
            }
        }
    }
    else if( value<0.5 && value>-0.5 )
    {
        last_la_x = 0;
    }
}

void ReXboxW::buttonAxisLyChanged(double value)
{
    if( last_la_y==0 )
    {
        if( value<-0.99 ) //up
        {
            last_la_y = 1;
            if(isNative)
            {
                emit buttonLAxisUp();
            }
            else
            {
                tcp->reboundSendKey("h",1);
            }
        }
        else if( value>0.99 ) //down
        {
            last_la_y = 1;
            if(isNative)
            {
                emit buttonLAxisDown();
            }
            else
            {
                tcp->reboundSendKey("i",1);
            }
        }
    }
    else if( value<0.5 && value>-0.5 )
    {
        last_la_y = 0;
    }
}

void ReXboxW::buttonAxisRxChanged(double value)
{
    if( last_la_x==0 )
    {
        if( value==1 )//Right
        {
            last_la_x = 1;
            if(isNative)
            {
                emit buttonRAxisRight();
            }
            else
            {
                tcp->reboundSendKey("j",1);
            }
        }
        else if( value==-1 )//Left
        {
            last_la_x = 1;
            if(isNative)
            {
                emit buttonRAxisLeft();
            }
            else
            {
                tcp->reboundSendKey("k",1);
            }
        }
    }
    else if( value<0.5 && value>-0.5 )
    {
        last_la_x = 0;
    }
}

void ReXboxW::buttonAxisRyChanged(double value)
{
//    qDebug() << value;
    if( last_ra_y==0 )
    {
        if( value<-0.99 ) //up
        {
            last_ra_y = 1;
            if(isNative)
            {
                emit buttonRAxisUp();
            }
            else
            {
                tcp->reboundSendKey("n",1);
            }
        }
        else if( value>0.99 ) //down
        {
            last_ra_y = 1;
            if(isNative)
            {
                emit buttonRAxisDown();
            }
            else
            {
                tcp->reboundSendKey("o",1);
            }
        }
    }
    else if( value<0.5 && value>-0.5 )
    {
        last_ra_y = 0;
    }
}

void ReXboxW::buttonStartChanged(bool value)
{
    qDebug() << "buttonStartChanged";
    if ( value==1 )
    {
        if(isNative)
        {
            emit buttonStartPressed();
        }
        else
        {
            tcp->reboundSendKey("m",1);
        }
    }
}

void ReXboxW::buttonSelectChanged(bool value)
{
    if ( value==1 )
    {
        if(isNative)
        {
            emit buttonSelectPressed();
        }
        else
        {
            tcp->reboundSendKey("s",1);
        }
    }
}

void ReXboxW::buttonCenterChanged(bool value)
{
    if ( value==1 )
    {
        if(isNative)
        {
            ///FIXME
//            emit buttonCenterChanged();
        }
        else
        {
            tcp->reboundSendKey("c",1);
        }
    }
}

void ReXboxW::buttonGuideChanged(bool value)
{
    //Filter out all unwanted guide press
    if ( state->hardware->timer_state==RE_TIMER_STATE_INIT )
    {
        if ( value )
        {
            if(isNative)
            {
                emit buttonGuidePressed();
            }
            else
            {
                tcp->reboundSendKey("g",1);
            }
    //        QMetaObject::invokeMethod(ui, "uiToggle");
        }
    }
}

void ReXboxW::buttonLeftChanged(bool value)
{
    if ( value==1 )
    {
        if(isNative)
        {
            emit buttonLeftPressed();
        }
        else
        {
            tcp->reboundSendKey("l",1);
        }
    }
}

void ReXboxW::buttonRightChanged(bool value)
{
    if ( value==1 )
    {
        if(isNative)
        {
            emit buttonRightPressed();
        }
        else
        {
            tcp->reboundSendKey("r",1);
        }
    }
}

void ReXboxW::buttonUpChanged(bool value)
{
    if ( value==1 )
    {
        if(isNative)
        {
            emit buttonUpPressed();
        }
        else
        {
            tcp->reboundSendKey("u",1);
        }
    }
}

void ReXboxW::buttonDownChanged(bool value)
{
    if ( value==1 )
    {
        if(isNative)
        {
            emit buttonDownPressed();
        }
        else
        {
            tcp->reboundSendKey("d",1);
        }
    }
}



