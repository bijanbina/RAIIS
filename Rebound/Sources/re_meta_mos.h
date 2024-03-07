#ifndef RE_META_MOS_H
#define RE_META_MOS_H

#include <QVector>
#include <QThread>

#include "backend.h"
#include "re_state.h"
#include "re_mouse.h"

class ReMetaMos
{
public:
    ReMetaMos();

    static void castCode(int val, CCommand *cmd);
    static void castMonitor(int val);
    static void castScroll(int val);
    static void castFirefox(int val, CCommand *cmd);
    static void castDiveSky(int cmd, int arg);
};

#endif // RE_META_MOS_H
