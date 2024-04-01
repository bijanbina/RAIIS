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

    static void castCode(int val, CCommand *cmd);
    static void castQt(int val, CCommand *cmd);
    static void castFirefox(int val, CCommand *cmd);
    static void castNautilus(int val, CCommand *cmd);
    static void csatGitKraken(int val, CCommand *cmd);
    static void castAltium(int val, CCommand *cmd);
    static void castSlack(int val, CCommand *cmd);
    static QString castXed(int val);
};

#endif // RE_META_FOX_H
