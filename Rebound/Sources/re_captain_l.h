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

    void execute(QVector<CaptainCommand> commands);
    bool isLastCmdRepeatable(QVector<CaptainCommand> commands);
    bool isLastMeta(QVector<CaptainCommand> commands);
    int keyCode2Digit(QString key_code);

    ReState *state;
private:
    void sendKey(int key_val);
    void pressKey(int key_val);
    void releaseKey(int key_val);
    void handleScroll(CaptainCommand command);

    void pressModifier(CaptainCommand command);
    void releaseModifiers();
    void setKey(int type, int code, int val);

    void execCommand(CaptainCommand command);

    bool isWakeUp(CaptainCommand command);

    int uinput_f;

    ReMetaL *meta;
    QVector<CaptainCommand> modifiers;
};



#endif // RE_CAPTAIN_H
