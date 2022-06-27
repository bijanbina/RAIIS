#ifndef RE_SUPER_H
#define RE_SUPER_H

#include <QVector>
#include <linux/uinput.h>

#include "backend.h"
#include "re_state.h"

class ReSuperL : public QObject
{
    Q_OBJECT

public:
    ReSuperL(ReState *st, QObject *parent = NULL);
    ~ReSuperL();

    void exec(CCommand command);

private:
    QString getGoCmd(int val);

    int uinput_f;

    ReState *state;
};

#endif //RE_SUPER_H
