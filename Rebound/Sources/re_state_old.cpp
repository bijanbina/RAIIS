#include "re_state_old.h"

ReStateOld::ReStateOld(QObject *parent) : QObject(parent)
{
    i_mode = RE_MODE_HIDDEN;
    ui_visible = false;
}

ReStateOld::~ReStateOld()
{
#ifdef _WIN32
    delete hardware;
#endif
}

void ReStateOld::toggleUi(QObject *item)
{
    i_mode = RE_MODE_MAIN;

    QMetaObject::invokeMethod(item, "uiToggle");
    ui_visible = QQmlProperty::read(item, "visible").toInt();
    if( !ui_visible )
    {
        i_mode = RE_MODE_HIDDEN;
    }
}
