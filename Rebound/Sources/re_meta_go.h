#ifndef RE_META_GO_H
#define RE_META_GO_H

#include <QVector>
#include <QThread>

#include "backend.h"
#include "re_state.h"

QString re_getGoQt(int val);
QString re_getGoXed(int val);
void re_castGoFirefox(int val, CCommand *cmd);
QString re_getGoNautilus(int val);
QString re_getGoGitKraken(int val);

#endif // RE_META_GO_H
