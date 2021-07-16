#ifndef RE_CAPTAIN_H
#define RE_CAPTAIN_H

#include <QVector>

#include <stdio.h>
#include <linux/uinput.h>

#include "backend.h"
#include "re_state.h"

#define RE_COMMAND_KEY   1
#define RE_COMMAND_NATO  2
#define RE_COMMAND_DIGIT 3
#define RE_COMMAND_MOD   4 //Modifiers
#define RE_COMMAND_META  5

typedef struct CaptainCommand
{
    int val1;
    int val2;
    int type;
}CaptainCommand;


class ReCaptainL : public QObject
{
    Q_OBJECT

public:
    ReCaptainL(ReState *st, QObject *parent = NULL);
    ~ReCaptainL();

    void execute(QVector<CaptainCommand> commands);
    bool isLastCmdReeatable(QVector<CaptainCommand> commands);
    int keyCode2Digit(QString key_code);

private:
    void sendKey(int key_val);
    void pressKey(int key_val);
    void releaseKey(int key_val);

    void pressModifier(CaptainCommand command);
    void releaseModifiers();
    void setKey(int type, int code, int val);

    int uinput_f;

    ReState *state;
    QVector<CaptainCommand> modifiers;
};



#endif // RE_CAPTAIN_H
