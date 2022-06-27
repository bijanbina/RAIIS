#ifndef RE_META_L_H
#define RE_META_L_H

#include <QVector>
#include <linux/uinput.h>

#include "backend.h"
#include "re_state.h"
#include "re_meta_go_l.h"
#include "re_meta_oc_l.h"

class ReMetaL : public QObject
{
    Q_OBJECT

public:
    ReMetaL(ReState *st, QObject *parent = NULL);
    ~ReMetaL();

    void execMeta(CCommand command);

private:
    QString getGoCmd(int val);
    QString getPageCmd(int val);
    QString getMusicCmd(int val);
    QString getMouseCmd(int val);
    QString getSystemCmd(int val);
    QString getTouchCmd(int val);
    void getScrollCmd(int meta, int val);

    int uinput_f;

    ReState *state;
};



#endif // RE_META_L_H
