#ifndef RE_MODIFIER_H
#define RE_MODIFIER_H

#include <QObject>
#include <QDebug>
#include "backend.h"
#include "re_commands.h"

CCommand re_modCreate(QString text);
void     re_modApplyVal(CCommand *cmd, int val);
void     re_modPress   (CCommand cmd);
void     re_modRelease (CCommand cmd);
void     re_modWait    (CCommand cmd, int val=20);

#endif // RE_MODIFIER_H
