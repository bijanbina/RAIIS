#ifndef RE_QT_H
#define RE_QT_H

#include <QVector>

#include "backend.h"
#include "re_state.h"

void re_qtDigitProc(QVector<CCommand> *cmd_buf, QString text);
bool re_qtDirProc(QVector<CCommand> *cmd_buf, QString text);

void re_getQtCmd(CCommand val);
QString re_getCloseQt(int val);
QString re_getOpenQt(int val);
CCommand re_getGoQt(QVector<CCommand> *cmd_buf);

void re_updateQtState(int buf);


#endif // RE_QT_H
