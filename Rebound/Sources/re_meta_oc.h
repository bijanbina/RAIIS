#ifndef RE_META_OC_H
#define RE_META_OC_H

// Open/Close Meta Function

#include <QVector>
#include <QThread>

#include "backend.h"
#include "re_state.h"
QString re_getCloseXed(int val);
QString re_getCloseFirefox(int val);
QString re_getCloseNautilus(int val);
QString re_getCloseGitKraken(int val);

QString re_getOpenXed(int val);
QString re_getOpenFirefox(int val);
QString re_getOpenNautilus(int val);
QString re_getOpenGitKraken(int val);

#endif // RE_META_OC_H
