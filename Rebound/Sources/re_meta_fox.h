#ifndef RE_META_FOX_H
#define RE_META_FOX_H

#include <QVector>
#include <QThread>

#include "backend.h"
#include "re_state.h"
#ifdef WIN32
#include "re_inject.h"
#endif

class ReMetaFox
{
public:
    ReMetaFox();
    void castCode(int val, CCommand *cmd);
    QString castXed(int val);
    void castFirefox(int val, CCommand *cmd);
    void castNautilus(int val, CCommand *cmd);
    void csatGitKraken(int val, CCommand *cmd);
    void castAltium(int val, CCommand *cmd);

private:
#ifdef WIN32
    ReInject *injector;
#endif
};

#endif // RE_META_FOX_H
