#ifndef RE_SUPER_H
#define RE_SUPER_H

#include <QVector>

#include "re_config.h"
#include "re_commands.h"
#include "re_mouse.h"
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
    ReSuper(ReWindow *current_w, QObject *parent = NULL);
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
    void getChessCmd(CCommand *ret, QString cmd);
    void getCommentCmd(CCommand *ret);
    void getSelectCmd(CCommand *ret);
    void makeNull(CCommand *ret);

    int uinput_f;

    ReWindow *app;

#ifdef WIN32
    void connectChessPipe();
    void sendPipe(const char *data);
    void recordTelegram();

    HANDLE hPipe;
    ReKeyEmulator key;
#endif
};

#endif //RE_SUPER_H
