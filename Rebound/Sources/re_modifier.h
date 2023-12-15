#ifndef RE_MODIFIER_H
#define RE_MODIFIER_H

#include <QObject>
#include <QDebug>
#include "backend.h"
#include "re_state.h"

CCommand re_modCreate(QString text);
void     re_modApplyVal(CCommand *cmd, int val);
void     re_modPress   (CCommand cmd);
void     re_modRelease (CCommand cmd);
void     re_modWait    (CCommand cmd);

#endif // RE_MODIFIER_H
