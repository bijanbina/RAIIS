#include "re_buttons.h"
#include <QThread>

ReButtons::ReButtons(QObject *item, ReState *st, QObject *parent) : QObject(parent)
{
    ui = item;
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
         QThread::msleep(200);
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
    state->toggleUi(ui);
}

void ReButtons::buttonGuidePressed()
{
    if( isUiVisible(ui) )
    {
         hideUI(ui);
         QThread::msleep(200);
         executeUi("select");
    }
    else
    {
        executeAhk("select_button");
    }
}

void ReButtons::buttonSelectPressed()
{
    if( isUiVisible(ui) )
    {
         hideUI(ui);
         QThread::msleep(200);
         executeUi("menu");
    }
    else
    {
        executeAhk("menu_button");
    }
}
#elif __linux__
void ReButtons::tab_timeout()
{
    timer_tab->stop();
    sendFakeEvent(0, XK_Alt_L); //A release
}

void ReButtons::buttonAPressed()
{
    if( isUiVisible(ui) )
    {
         hideUI(ui);
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
    if( isUiVisible(ui) )
    {
         hideUI(ui);
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
    if( isUiVisible(ui) )
    {
         hideUI(ui);
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

    if( isUiVisible(ui) )
    {
         hideUI(ui);
         system("xdotool key XF86AudioMute &");
    }
    else
    {
        if( !timer_tab->isActive() )
        {
             sendFakeEvent(1, XK_Alt_L); //ALT_L press
        }

//        if( isNative )
//        {
//            qDebug() <<  "Alt P" << isNative;
////            QThread::msleep(100);
//        }
//        qDebug() <<  "Next Window" << isNative;
        system("xdotool key Tab &");
        timer_tab->start(RE_TAB_TIME);
    }
}

void ReButtons::buttonGuidePressed()
{
//    system("xdotool key Escape &");
    QMetaObject::invokeMethod(ui, "uiToggle");
}

#endif
