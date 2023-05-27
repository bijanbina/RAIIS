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

class ReSuper : public QObject
{
    Q_OBJECT

public:
    ReSuper(ReState *st, QObject *parent = NULL);
    ~ReSuper();

    void castCmd(int cmd, CCommand *ret);

#ifdef WIN32
    ReWin32Virt *virt;
#endif
private:
    void getMetaCmd(CCommand *ret);
    void getCopyCmd(CCommand *ret);
    void getPasteCmd(CCommand *ret);
    void getLoveCmd(CCommand *ret);
    void getRogerCmd(CCommand *ret);
    void getSwitchCmd(CCommand *ret);
    void getLSwitchCmd(CCommand *ret);
    void getCamelCmd(CCommand *ret);
    void getSelectCmd(CCommand *ret);
    void makeNull(CCommand *ret);

    int uinput_f;
    ReState  *state;

#ifdef WIN32
    void recordTelegram();
    ReKeyEmulator key;
#endif
};

#endif //RE_SUPER_H
