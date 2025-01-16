#ifndef RE_META_H
#define RE_META_H

#include <QVector>

#include "backend.h"
#include "re_state.h"
#include "re_meta_fox.h"
#include "re_meta_power.h"
#include "re_meta_oc.h"
#include "re_bisper.h"
#include "re_meta_mos.h"
#ifdef WIN32
#include <windows.h>
#include "re_app_w.h"
#include "re_pipe.h"
#include "mm_api.h"
#else
#include "re_app_l.h"
#endif

class ReMeta
{
public:
    ReMeta();

    static CCommand castMeta(int meta, int arg);

private:
    static void execOpen(MmApplication *app);
    static void castOpenCmd(int val, CCommand *cmd);
    static void castMusicCmd(int val, CCommand *cmd);
    static void castMouseCmd(int val, CCommand *cmd);
    static void castTouchCmd(int val, CCommand *cmd);
    static void castSystemCmd(int val, CCommand *cmd);
    static void castFoxCmd(int val, CCommand *cmd);
    static void castPowerCmd(int val, CCommand *cmd);
    static void sendChessCmd(QString cmd, QString arg="");
};

#endif // RE_META_H
