#include "re_buttons.h"
#include <QThread>

ReButtons::ReButtons(QObject *item, QObject *parent) : QObject(parent)
{
    ui = item;
}

void ReButtons::buttonAPressed()
{
    if( isUiVisible(ui) )
    {
         hideUI(ui);
         QThread::msleep(200);
         executeUi("a");
    }
    else
    {
        executeAhk("button_a");
    }
}

void ReButtons::buttonBPressed()
{
    if( isUiVisible(ui) )
    {
         hideUI(ui);
         QThread::msleep(200);
         executeUi("b");
    }
    else
    {
        executeAhk("button_b");
    }
}

void ReButtons::buttonXPressed()
{
    if( isUiVisible(ui) )
    {
         hideUI(ui);
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
    if( isUiVisible(ui) )
    {
         hideUI(ui);
         QThread::msleep(200);
         executeUi("y");
    }
    else
    {
        executeAhk("button_y");
    }
}

void ReButtons::buttonStartPressed()
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

void ReButtons::buttonGuidePressed()
{
    QMetaObject::invokeMethod(ui, "uiToggle");
}

void ReButtons::buttonSelectPressed()
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
