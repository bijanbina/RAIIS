#ifndef RE_META_H
#define RE_META_H

#include <QVector>

#include "backend.h"
#include "re_state.h"
#include "re_meta_go.h"
#include "re_meta_oc.h"
#ifdef WIN32
#include <windows.h>
#include "re_app_w.h"
#else
#include "re_app_l.h"
#endif

class ReMeta : public QObject
{
    Q_OBJECT

public:
    ReMeta(ReState *st, QObject *parent = NULL);
    ~ReMeta();

    CCommand castMeta(int meta, int arg);

private:
    void castGoCmd(int val, CCommand *cmd);
    void castPageCmd(int val, CCommand *cmd);
    void castMusicCmd(int val, CCommand *cmd);
    void castMouseCmd(int val, CCommand *cmd);
    void castTouchCmd(int val, CCommand *cmd);
    void castSystemCmd(int val, CCommand *cmd);
    void castFoxCmd(int val, CCommand *cmd);
    void execScrollCmd(int meta, int val);

    void moveMouseR(int x, int y);

    ReState *state;
};



#endif // RE_META_H
