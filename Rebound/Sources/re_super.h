#ifndef RE_SUPER_H
#define RE_SUPER_H

#include <QVector>

#include "re_config.h"
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

private:
    void getMetaCmd(CCommand *ret);
    void getCopyCmd(CCommand *ret);
    void getPasteCmd(CCommand *ret);
    void getLoveCmd(CCommand *ret);
    void getRogerCmd(CCommand *ret);
    void getSwitchCmd(CCommand *ret);
    void getCamelCmd();
    void getSideCmd();
    void getKickCmd();

    void connectChessPipe();
    void sendPipe(const char *data);

    int uinput_f;

    ReState *state;

    HANDLE hPipe;
    ReWin32Virt *virt;
};

#endif //RE_SUPER_H
