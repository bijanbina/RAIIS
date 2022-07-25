#ifndef RE_CAPTAIN_H
#define RE_CAPTAIN_H

#include <QVector>

#include <stdio.h>

#include "backend.h"
#include "re_meta.h"
#include "re_super.h"
#include "re_qt.h"
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
    ReKeyboard  *key;
private:
    void handleScroll(CCommand command);

    void execModifier(CCommand command);
    void releaseModifiers();

    void execCommand(CCommand command);

    bool isWakeUp(CCommand command);

    int uinput_f;

    ReMeta  *meta;
    QVector<CCommand> modifiers;
};

#endif // RE_CAPTAIN_H
