#ifndef RE_SUPER_H
#define RE_SUPER_H

#include <QVector>

#include "backend.h"
#include "re_state.h"
#ifdef WIN32
#include "re_app_w.h"
#include "re_keyboard_w.h"
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
    void getSideCmd();
    void getKickCmd();

    int uinput_f;

    ReState *state;
};

#endif //RE_SUPER_H
