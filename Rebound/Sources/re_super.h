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
    ReSuper(ReState *st);

    void castCmd(int val, CCommand *cmd);

private:
    void castMetaCmd (CCommand *cmd);
    void castCopyCmd (CCommand *cmd);
    void castPasteCmd(CCommand *cmd);
    void castLoveCmd (CCommand *cmd);
    void castRogerCmd(CCommand *cmd);
    void castFrontCmd(CCommand *cmd);
    void castLastCmd (CCommand *cmd);

    void castSwitchCmd(CCommand *cmd);
    void castLSwitchCmd(CCommand *cmd);
    void castCamelCmd(CCommand *cmd);
    void castSelectCmd(CCommand *cmd);
    void makeNull(CCommand *cmd);

    // super_app
    void castRunCmd(CCommand *cmd);

    int uinput_f;
    ReState  *state;

#ifdef WIN32
    void recordTelegram();
#endif
    ReKeyboard key;
};

#endif //RE_SUPER_H
