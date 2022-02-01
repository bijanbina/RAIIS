#ifndef RE_CAPTAIN_H
#define RE_CAPTAIN_H

#include <QVector>

#include <stdio.h>
#include <linux/uinput.h>

#include "backend.h"
#include "re_meta_l.h"

class ReCaptainL : public QObject
{
    Q_OBJECT

public:
    ReCaptainL(ReState *st, QObject *parent = NULL);
    ~ReCaptainL();

    void execute(QVector<CCommand> commands);
    bool isLastRepeatable();

    ReState *state;
    CCommand last_cmd;
private:
    void sendKey(int key_val);
    void pressKey(int key_val);
    void releaseKey(int key_val);
    void handleScroll(CCommand command);

    void pressModifier(CCommand command);
    void releaseModifiers();
    void setKey(int type, int code, int val);

    void execCommand(CCommand command);

    bool isWakeUp(CCommand command);

    int uinput_f;

    ReMetaL *meta;
    QVector<CCommand> modifiers;
};



#endif // RE_CAPTAIN_H
