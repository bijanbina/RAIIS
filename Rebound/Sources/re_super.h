#ifndef RE_SUPER_H
#define RE_SUPER_H

#include <QVector>

#include "re_config.h"
#include "re_commands.h"
#include "re_mouse.h"
#include "re_state.h"
#ifdef WIN32
#include "re_app_w.h"
#include "re_keyboard_w.h"
#include "re_win32_virt.h"
#else
#include "re_keyboard_l.h"
#include "re_app_l.h"
#endif

class ReSuper
{
public:
    ReSuper();

    static void cast(int val, CCommand *cmd);
    static void castMetaCmd (CCommand *cmd);
    static void castCopyCmd (CCommand *cmd);
    static void castPasteCmd(CCommand *cmd);
    static void castLoveCmd (CCommand *cmd);
    static void castRogerCmd(CCommand *cmd);
    static void castFrontCmd(CCommand *cmd);
    static void castLastCmd (CCommand *cmd);

    static void castSwitchCmd(CCommand *cmd);
    static void castLSwitchCmd(CCommand *cmd);
    static void castCamelCmd(CCommand *cmd);
    static void castSelectCmd(CCommand *cmd);
    static void makeNull(CCommand *cmd);

    // super_app
    static void castRunCmd(CCommand *cmd);

#ifdef WIN32
    static void recordTelegram();
#endif
    static ReKeyboard key;
};

#endif //RE_SUPER_H
