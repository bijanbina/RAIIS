#ifndef RE_CAPTAIN_H
#define RE_CAPTAIN_H

#include <QVector>

#include <stdio.h>

#include "backend.h"
#include "re_meta.h"
#include "re_super.h"
#include "re_qt.h"
#include "re_modifier.h"
#include "re_chess.h"
#ifdef WIN32
#include "re_keyboard_w.h"
#else
#include "re_keyboard_l.h"
#endif

class ReCaptain : public QObject
{
    Q_OBJECT

public:
    ReCaptain(QObject *parent = NULL);
    ~ReCaptain();

    void execute(QVector<CCommand> commands);
    bool isLastRepeatable();

private:
    void handleScroll(CCommand command);

    void execKeyboard(CCommand command);
    void execMeta (CCommand command);
    void execChess(CCommand command);
    void execMouse(CCommand command);

    int execSleep(CCommand command);
    void execCommand(CCommand command);
    void wakeDictate();
    void wakeRecord();

    bool isWakeUp(CCommand command);
    bool isSpeakerSw(CCommand command);

    int uinput_f;

    QVector<CCommand> modifiers;
};

#endif // RE_CAPTAIN_H
