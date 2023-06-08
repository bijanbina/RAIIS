#ifndef RE_META_GO_H
#define RE_META_GO_H

#include <QVector>
#include <QThread>

#include "backend.h"
#include "re_state.h"

void re_getGoCode(int val, CCommand *cmd);
QString re_getGoXed(int val);
void re_castGoFirefox(int val, CCommand *cmd);
void re_getGoNautilus(int val, CCommand *cmd);
void re_getGoGitKraken(int val, CCommand *cmd);

#endif // RE_META_GO_H
