#ifndef RE_STATUS_FILE_H
#define RE_STATUS_FILE_H

#include <QObject>
#include <QString>
#include <QQmlProperty>
#include <QFileInfo>
#include "backend.h"
#include "re_state_const.h"

QString re_readStatus();
void    re_rmStatus();
void    re_rmSpex();

#endif //RE_STATUS_FILE_H
