#include "re_buttons.h"
#include <QThread>
#include "re_hardware_w.h"

ReButtons::ReButtons(QObject *item, QObject *switcher, ReState *st, QObject *parent) : QObject(parent)
{
    ui = item;
    uiSwitcher = switcher;
    state = st;

#if __linux__
    reX11_init();

    //switching tab
    timer_tab = new QTimer;
//    timer_tab->setSingleShot(true);
    connect(timer_tab, SIGNAL(timeout()), this, SLOT(tab_timeout()));
#endif
}

#ifdef _WIN32
void ReButtons::buttonAPressed()
{
    if( state->ui_visible )
    {
        state->propageteMode(RE_MODE_APPLICATION);
    }
    else
    {
        executeAhk("button_a");
    }
}

void ReButtons::buttonBPressed()
{
    if( state->ui_visible )
    {
         state->propageteMode(RE_MODE_SPOTIFY);
    }
    else
    {
        executeAhk("button_b");
    }
}

void ReButtons::buttonXPressed()
{
    if( state->ui_visible )
    {
         state->toggleUi(ui);
         QThread::msleep(20);
         executeUi("x");
    }
    else
    {
        executeAhk("button_x");
    }
}

void ReButtons::buttonYPressed()
{
    if( state->ui_visible )
    {
        state->propageteMode(RE_MODE_SWITCH);
    }
    else
    {
        executeAhk("button_y");
    }
}

void ReButtons::buttonStartPressed()
{
    if( state->ui_visible )
    {
        if ( state->getMode()==RE_MODE_APPLICATION )
        {
            state->toggleUi(ui);
            state->api->openApp(RE_PROC_TELEGRAM);
            qDebug() << "openApp";
        }
        else
        {
            state->toggleUi(ui);
        }
    }
    else
    {
        state->toggleUi(ui);
    }
}

void ReButtons::buttonGuidePressed()
{
    if( state->ui_visible )
    {
//        state->toggleUi(ui);
//        QThread::msleep(20);
//        executeUi("select");
        state->hardware->disconnectXbox();
    }
    else
    {
        executeAhk("select_button");
    }
}

void ReButtons::buttonSelectPressed()
{
    if( state->ui_visible )
    {
        state->toggleUi(ui);
        QThread::msleep(20);
        executeUi("button_select");
    }
    else
    {
        if( isItemVisible(uiSwitcher) )
        {
            QMetaObject::invokeMethod(uiSwitcher, "activeNextProcess");
        }
        else
        {
            state->showSwither(uiSwitcher);
        }
    }
}
#elif __linux__
int sh_alt_down = 0;
int sh_child_count = 0;

void ReButtons::tab_timeout()
{
    timer_tab->stop();
//    sendFakeEvent(0, XK_Alt_L); //A release
//    system("xdotool keyup 0xffea &");
    qDebug() <<  "Release Window";
}

void ReButtons::buttonAPressed()
{
    if( isItemVisible(ui) )
    {
         hideItem(ui);
         system("./Scripts/focus_window spotify");
    }
    else
    {
        system("./Scripts/button_a &");
    }
}

void ReButtons::buttonBPressed()
{
    system("./Scripts/button_b &");
}

void ReButtons::buttonXPressed()
{
    if( isItemVisible(ui) )
    {
         hideItem(ui);
         QThread::msleep(200);
         system("xdotool key Alt+F4 &");
    }
    else
    {
        system("./Scripts/button_x &");
    }
}

void ReButtons::buttonYPressed()
{
    if( isItemVisible(ui) )
    {
         hideItem(ui);
         system("./Scripts/focus_window firefox");
    }
    else
    {
        system("./Scripts/button_y &");
    }
}

void ReButtons::buttonStartPressed()
{
    qDebug() <<  "Enable autoscroll";
    system("./Scripts/menu_button &");
}

//in native mode add sleep
void ReButtons::buttonSelectPressed()
{

    if( isItemVisible(ui) )
    {
         hideItem(ui);
         system("xdotool key XF86AudioMute &");
    }
    else
    {
        re_getWindowList();
    }
}

void ReButtons::buttonGuidePressed()
{
//    system("xdotool key Escape &");
    QMetaObject::invokeMethod(ui, "uiToggle");
}

#endif
