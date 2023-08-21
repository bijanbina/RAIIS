#include "re_chapar.h"
#include <QDebug>
#include <QQmlProperty>

ReChapar::ReChapar(QObject *item, QObject *switcher,
                   int isNative, QObject *parent) : QObject(parent)
{
    ui = item;
    uiSwitcher = switcher;

    api   = new ReApi;
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
    thread_data->key = captain->key;

    sync_thread_timer = new QTimer(this); //FIXME: This line is
    api_thread = new std::thread(reRunThread, (void *)thread_data);

    controller = new ReXboxW(state);
    connect(controller, SIGNAL(requstSuspend()), this, SLOT(requstSuspend()));

    channel = new ReChannelW(captain);
    remote = new ReRemote(channel->pre);
    channel_thread = new QThread();
    channel->moveToThread(channel_thread);

    connect(this, SIGNAL(startChannel()), channel, SLOT(ListenPipe()));
    connect(channel, SIGNAL(sendRemote(QString, QString)),
            remote, SLOT(send(QString, QString)));
    channel_thread->start();

    emit startChannel();
#else
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
        if ( title[i].unicode()==65533 )
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

}

void ReChapar::switchWindow(int index)
{
    state->i_mode = RE_MODE_HIDDEN;
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
