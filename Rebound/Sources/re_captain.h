#ifndef RE_CAPTAIN_H
#define RE_CAPTAIN_H

#include <QVector>

#include <stdio.h>

#include "backend.h"
#include "re_meta.h"
#include "re_super.h"
#include "re_qt.h"
#include "re_modifier.h"
#ifdef WIN32
#include "re_keyboard_w.h"
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

    ReState     *state;
    ReSuper     *super;
private:
    void handleScroll(CCommand command);

    void execKeyboard(CCommand command);
    void execMeta(CCommand command);

    void execCommand(CCommand command);
    void wakeDictate();
    void wakeRecord();

    bool isWakeUp(CCommand command);
    bool isSpeakerSw(CCommand command);

    int uinput_f;

    ReMeta  *meta;
    QVector<CCommand> modifiers;
};

#endif // RE_CAPTAIN_H
