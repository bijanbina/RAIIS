#include "re_chapar.h"
#include <QDebug>
#include <QQmlProperty>

ReChapar::ReChapar(QObject *item, QObject *switcher,
                   int isNative, QObject *parent) : QObject(parent)
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

    window = new ReWindowW(state);
    window_thread = new QThread();
    window->moveToThread(window_thread);
    window_thread->start();
    window->wins_title = &(state->wins_title);
    window->elems_name = &(state->elems_name);

    connect(this, SIGNAL(startChannel()),
            window, SLOT(start()));

//    controller = new ReXboxW(state);
//    connect(controller, SIGNAL(requstSuspend()),
//            this, SLOT(requstSuspend()));

    channel = new ReChannelW(captain);
    channel_thread = new QThread();
    channel->moveToThread(channel_thread);
    connect(this, SIGNAL(startChannel()), channel,
            SLOT(ListenPipe()));
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
    remote = new ReRemote(channel->pre);
    connect(channel, SIGNAL(sendRemote(QString)),
            remote, SLOT(send(QString)));
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
