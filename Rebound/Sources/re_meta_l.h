#ifndef RE_META_L_H
#define RE_META_L_H

#include <QVector>
#include <linux/uinput.h>

#include "backend.h"
#include "re_state.h"

typedef struct CaptainCommand
{
    int val1;
    int val2;
    int val3;
    int type;
}CaptainCommand;


class ReMetaL : public QObject
{
    Q_OBJECT

public:
    ReMetaL(ReState *st, QObject *parent = NULL);
    ~ReMetaL();

    void execMeta(CaptainCommand command);

private:
    QString getMusicCmd(int val);
    QString getSystemCmd(int val);
    QString getSwitchCmd(int val);
    QString getScrollCmd(bool scroll_mode, int meta, int val);

    int uinput_f;

    ReState *state;
};



#endif // RE_META_L_H
