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
int sh_alt_down = 0;
int sh_child_count = 0;

void ReButtons::tab_timeout()
{
    timer_tab->stop();
//    sendFakeEvent(0, XK_Alt_L); //A release
    system("xdotool keyup 0xffea &");
    qDebug() <<  "Release Window";
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
        if( sh_alt_down )
        {
            int is_parent = fork();
            if ( is_parent==0 ) //in the child
            {
                sh_child_count++;
                system("xdotool key Tab");
                qDebug() <<  "Alt P";

                usleep(400000);
                sh_child_count--;

                if( sh_child_count==0 )
                {
                    system("xdotool keyup 0xffea &");
                }
            }
        }
        else
        {
            int is_parent = fork();
            if ( is_parent==0 ) //in the child
            {
                sh_child_count++;
                system("xdotool keydown 0xffea + key 0xff09");
                qDebug() <<  "Tab";

                usleep(400000);
                sh_child_count--;

                if( sh_child_count==0 )
                {
                    system("xdotool keyup 0xffea &");
                }
            }
        }

//        if( isNative )
//        {
//        }
//        qDebug() <<  "b_183";
//        sendFakeEvent(1, XK_BackSpace); //Tab press
//        qDebug() <<  "b_184";
////        QThread::msleep(1);
//        sendFakeEvent(0 , XK_BackSpace); //Tab release
//        qDebug() <<  "b_185";
//        sendXFlush()  ;
        timer_tab->start(RE_TAB_TIME);
    }
}

void ReButtons::buttonGuidePressed()
{
//    system("xdotool key Escape &");
    QMetaObject::invokeMethod(ui, "uiToggle");
}

#endif
