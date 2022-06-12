#ifndef RE_META_OC_L_H
#define RE_META_OC_L_H

// Open/Close Meta Function

#include <QVector>
#include <QThread>
#include <linux/uinput.h>

#include "backend.h"
#include "re_state.h"

void re_digitQtProc(QVector<CCommand> *cmd_buf, QString text);
bool re_dirQtProc(QVector<CCommand> *cmd_buf, QString text);

QString re_getCloseCmd(ReState *state, int val);
QString re_getCloseQt(int val);
QString re_getCloseXed(int val);
QString re_getCloseFirefox(int val);
QString re_getCloseNautilus(int val);
QString re_getCloseGitKraken(int val);

QString re_getOpenCmd(ReState *state, int val);
QString re_getOpenQt(int val);
QString re_getOpenXed(int val);
QString re_getOpenFirefox(int val);
QString re_getOpenNautilus(int val);
QString re_getOpenGitKraken(int val);

void re_updateQtState(int buf);

#endif // RE_META_OC_L_H
