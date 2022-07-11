#include "re_chapar.h"
#include <QDebug>
#include <QQmlProperty>

ReChapar::ReChapar(QObject *item, QObject *switcher, int isNative, QObject *parent) : QObject(parent)
{
    ui = item;
    uiSwitcher = switcher;

    state = new ReState;
    bumpers = new ReBumpers(ui, switcher, state);
    buttons = new ReButtons(ui, switcher, state);
    directions = new ReDirections(ui, state);
    laxis = new ReLAxis(ui, state);
    raxis = new ReRAxis(ui, state);
    captain = new ReCaptain(state);

#ifdef WIN32
    thread_data = new threadStruct;
    thread_data->wins_title = &(state->api->wins_title);
    thread_data->elems_name = &(state->api->elems_name);
    thread_data->state = state;

    sync_thread_timer = new QTimer(this); //FIXME: This line is
    api_thread = new std::thread(reRunThread, (void *)thread_data);

    controller = new ReXboxW(state);
    connect(controller, SIGNAL(requstSuspend()), this, SLOT(requstSuspend()));
#else
    api = new ReApiL;
    controller = new ReXboxL(item, isNative);
    channel = new ReChannelL(captain, ui);

    thread_data = new threadStruct;
    thread_data->wins_title = &(api->wins_title);
    thread_data->elems_name = &(api->elems_name);
    thread_data->state = state;

    Display *disp = reX11_init();
    api->setDisplay(disp);
    api_thread = new std::thread(reRunThread, (void *)thread_data);
#endif

    connect(controller, SIGNAL(buttonAPressed()), buttons, SLOT(buttonAPressed()));
    connect(controller, SIGNAL(buttonBPressed()), buttons, SLOT(buttonBPressed()));
    connect(controller, SIGNAL(buttonXPressed()), buttons, SLOT(buttonXPressed()));
    connect(controller, SIGNAL(buttonYPressed()), buttons, SLOT(buttonYPressed()));
    connect(controller, SIGNAL(buttonGuidePressed()) , buttons, SLOT(buttonGuidePressed()));
    connect(controller, SIGNAL(buttonSelectPressed()), buttons, SLOT(buttonSelectPressed()));
    connect(controller, SIGNAL(buttonStartPressed()) , buttons, SLOT(buttonStartPressed()));

    connect(controller, SIGNAL(buttonL1Pressed()), bumpers, SLOT(buttonL1Pressed()));
    connect(controller, SIGNAL(buttonL2Pressed()), bumpers, SLOT(buttonL2Pressed()));
    connect(controller, SIGNAL(buttonR1Pressed()), bumpers, SLOT(buttonR1Pressed()));
    connect(controller, SIGNAL(buttonR2Pressed()), bumpers, SLOT(buttonR2Pressed()));

    connect(controller, SIGNAL(buttonRightPressed()), directions, SLOT(buttonRightPressed()));
    connect(controller, SIGNAL(buttonDownPressed()) , directions, SLOT(buttonDownPressed()));
    connect(controller, SIGNAL(buttonLeftPressed()) , directions, SLOT(buttonLeftPressed()));
    connect(controller, SIGNAL(buttonUpPressed())   , directions, SLOT(buttonUpPressed()));

    connect(controller, SIGNAL(buttonLAxisRight()) , laxis, SLOT(buttonRightPressed()));
    connect(controller, SIGNAL(buttonLAxisDown())  , laxis, SLOT(buttonDownPressed()));
    connect(controller, SIGNAL(buttonLAxisLeft())  , laxis, SLOT(buttonLeftPressed()));
    connect(controller, SIGNAL(buttonLAxisUp())    , laxis, SLOT(buttonUpPressed()));

    connect(controller, SIGNAL(buttonRAxisRight()) , raxis, SLOT(buttonRightPressed()));
    connect(controller, SIGNAL(buttonRAxisDown())  , raxis, SLOT(buttonDownPressed()));
    connect(controller, SIGNAL(buttonRAxisLeft())  , raxis, SLOT(buttonLeftPressed()));
    connect(controller, SIGNAL(buttonRAxisUp())    , raxis, SLOT(buttonUpPressed()));

    connect(state, SIGNAL(updateMode()), this, SLOT(updateMode()));

    connect(uiSwitcher, SIGNAL(selectWindow(int)), this, SLOT(switchWindow(int)));
}

QString ReChapar::getShortTitle(int index)
{
    QString title = api->getWinTitle(index);

    for ( int i=0 ; i<title.length() ; i++ )
    {
        if ( title[i].unicode() == 65533 )
        {
            return title.left(i);
        }
    }

    if ( title.length()>20 )
    {
        qDebug() << title[19].unicode() << title[18] << title[17];
        return  title.left(20);
    }

    return title;
}

void ReChapar::updateMode()
{
#ifdef _WIN32
    RePage c_page; // current page
    if( state->getMode()==RE_MODE_MAIN )
    {
        c_page.x_action = "Close Active Application";
        c_page.y_action = "Switch Application";
        c_page.a_action = "Open Application";
        c_page.b_action = "Control Music";
        c_page.s_action = "Open New Firefox Window";

        c_page.r1_action = getShortTitle(0);
        c_page.r2_action = getShortTitle(1);
        c_page.l1_action = getShortTitle(2);
        c_page.l2_action = getShortTitle(3);
        c_page.m_action = "Close Super Mode";

        c_page.left_action = "Switch to Workspace #1";
        c_page.up_action = "Switch to Workspace #2";
        c_page.down_action = "Switch to Workspace #3";
        c_page.right_action = "Switch to Workspace #4";

        c_page.axis_state = "1";
    }
    else if( state->getMode()==RE_MODE_APPLICATION )
    {
        c_page.x_action = "Open Firefox";
        c_page.y_action = "Open Spotify";
        c_page.a_action = "Open Telegram";
        c_page.b_action = "Connect VPN";
        c_page.s_action = "Suspend the PC";

        c_page.r1_action = "Qt Creator";
        c_page.r2_action = "Git Kraken";
        c_page.l1_action = "Allegro 17.4";
        c_page.l2_action = "Allegro 17.2";
        c_page.m_action = "Close Super Mode";

        c_page.lau_action = "Sajad jooOon";
        c_page.lad_action = "Bijan Joon";
        c_page.lal_action = "Karim joon";
        c_page.lar_action = "Ehsan Joon";
        c_page.rau_action = "Abdi joooon";
        c_page.rad_action = "Aflatoon joon";
        c_page.ral_action = "Narges joon";
        c_page.rar_action = "Sepehr joon";
        c_page.left_action = "Switch to Workspace #1";
        c_page.up_action = "Switch to Workspace #2";
        c_page.down_action = "Switch to Workspace #3";
        c_page.right_action = "Switch to Workspace #4";
        c_page.axis_state = "0";


        if ( re_isVpnConnected() )
        {
            c_page.b_action = "Disconnect VPN";
        }
    }
    else if( state->getMode()==RE_MODE_SWITCH )
    {
        c_page.x_action = state->api->getWinTitle(0);
        c_page.y_action = state->api->getWinTitle(1);
        c_page.a_action = state->api->getWinTitle(2);
        c_page.b_action = state->api->getWinTitle(3);
        c_page.s_action = state->api->getWinTitle(4);

        c_page.r1_action = state->api->getWinTitle(5);
        c_page.r2_action = state->api->getWinTitle(6);
        c_page.l1_action = state->api->getWinTitle(7);
        c_page.l2_action = state->api->getWinTitle(8);

        if(thread_data->message.isEmpty())
        {
            thread_data->message = "Launch Nuclear missiles";
        }
    }
    /*if( state->getProcess()==RE_WIN_EXPLORER )
    {
        ;
    }
    else if( state->getProcess()==RE_WIN_FIREFOX )
    {
        ;
    }
    else if( state->getProcess()==RE_WIN_QT )
    {
        ;
    }
    else if( state->getProcess()==RE_WIN_READING )
    {
        ;
    }*/
    else if( state->getMode()==RE_MODE_SPOTIFY )
    {
        c_page.x_action = "Play/Pause";
        c_page.y_action = "Repeat Mode";
        c_page.a_action = "Like Song";
        c_page.b_action = "Stop Music";
        c_page.m_action = "Close Super Mode";
        c_page.s_action = "Mute/UnMute";

        c_page.r1_action = "Next Music";
        c_page.l1_action = "Prev Music";
        c_page.r2_action = "Increase Volume";
        c_page.l2_action = "Decrease Volume";

        c_page.lau_action = "-40% Volume";
        c_page.lar_action = "-30% Volume";
        c_page.lal_action = "-20% Volume";
        c_page.lad_action = "-10% Volume";
        c_page.rau_action = "+40% Volume";
        c_page.rar_action = "+30% Volume";
        c_page.ral_action = "+20% Volume";
        c_page.rad_action = "+10% Volume";

//        c_page.lau_action = state->api->getElemName(0).split(" ")[0];
//        c_page.lar_action = state->api->getElemName(1).split(" ")[0];
//        c_page.lal_action = state->api->getElemName(2).split(" ")[0];
//        c_page.lad_action = state->api->getElemName(3).split(" ")[0];
//        c_page.rau_action = state->api->getElemName(4).split(" ")[0];
//        c_page.rar_action = state->api->getElemName(5).split(" ")[0];
//        c_page.ral_action = state->api->getElemName(6).split(" ")[0];
//        c_page.rad_action = state->api->getElemName(7).split(" ")[0];
    }
    setPage(c_page);
#endif
}

void ReChapar::switchWindow(int index)
{
    state->setMode(RE_MODE_HIDDEN);
    int i = index - 1;

    if ( i<thread_data->windows.size() )
    {
        ReWindow buffer = thread_data->windows[i];
        thread_data->windows.remove(i);
        thread_data->windows.push_front(buffer);

        state->updateApp(buffer);

        QString buffer_t = api->wins_title[i];
        api->wins_title.removeAt(i);
        api->wins_title.push_front(buffer_t);

        qDebug() << "switchWindow" << i << thread_data->windows[0].title;
        api->setActiveWindow(thread_data->windows[0].hWnd);
    }
}

void ReChapar::requstSuspend()
{
#ifdef _WIN32
    state->hardware->disconnectXbox();
#endif
}

void ReChapar::setPage(RePage page)
{
    QQmlProperty::write(ui, "x_action", page.x_action);
    QQmlProperty::write(ui, "y_action", page.y_action);
    QQmlProperty::write(ui, "a_action", page.a_action);
    QQmlProperty::write(ui, "b_action", page.b_action);
    QQmlProperty::write(ui, "m_action", page.m_action);
    QQmlProperty::write(ui, "s_action", page.s_action);
    QQmlProperty::write(ui, "r1_action", page.r1_action);
    QQmlProperty::write(ui, "r2_action", page.r2_action);
    QQmlProperty::write(ui, "l1_action", page.l1_action);
    QQmlProperty::write(ui, "l2_action", page.l2_action);
    QQmlProperty::write(ui, "lau_action", page.lau_action);
    QQmlProperty::write(ui, "lad_action", page.lad_action);
    QQmlProperty::write(ui, "lal_action", page.lal_action);
    QQmlProperty::write(ui, "lar_action", page.lar_action);
    QQmlProperty::write(ui, "rau_action", page.rau_action);
    QQmlProperty::write(ui, "rad_action", page.rad_action);
    QQmlProperty::write(ui, "ral_action", page.ral_action);
    QQmlProperty::write(ui, "rar_action", page.rar_action);
    QQmlProperty::write(ui, "left_action", page.left_action);
    QQmlProperty::write(ui, "up_action", page.up_action);
    QQmlProperty::write(ui, "down_action", page.down_action);
    QQmlProperty::write(ui, "right_action", page.right_action);
    QQmlProperty::write(ui, "axis_state", page.axis_state);
}
