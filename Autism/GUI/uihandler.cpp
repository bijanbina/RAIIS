#include "uihandler.h"

UiHandler::UiHandler(QObject *ui,QObject *parent) : QObject(parent)
{
    root = ui;
}

