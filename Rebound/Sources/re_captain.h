#ifndef RE_CAPTAIN_H
#define RE_CAPTAIN_H

#include <QVector>

#include <stdio.h>

#include "backend.h"
#include "re_meta_l.h"
#include "re_super_l.h"
#include "re_qt.h"
#ifdef WIN32
//#include "re_keyboard_w.h"
#else
#include "re_keyboard_l.h"
#endif

class ReCaptain : public QObject
{
    Q_OBJECT

public:
    ReCaptain(ReState *st, QObject *parent = NULL);
    ~ReCaptain();

    void execute(QVector<CCommand> commands);
    bool isLastRepeatable();
    void sendKey(int key_val);

    ReState *state;
private:
    void initLinux();
    void pressKey(int key_val);
    void releaseKey(int key_val);
    void handleScroll(CCommand command);

    void execModifier(CCommand command);
    void releaseModifiers();
    void setKey(int type, int code, int val);

    void execCommand(CCommand command);

    bool isWakeUp(CCommand command);

    int uinput_f;

    ReMetaL  *meta;
    ReSuperL *super;
    QVector<CCommand> modifiers;
};



#endif // RE_CAPTAIN_H
