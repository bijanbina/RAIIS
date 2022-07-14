#ifndef RE_META_H
#define RE_META_H

#include <QVector>

#include "backend.h"
#include "re_state.h"
#include "re_meta_go.h"
#include "re_meta_oc.h"

class ReMeta : public QObject
{
    Q_OBJECT

public:
    ReMeta(ReState *st, QObject *parent = NULL);
    ~ReMeta();

    void execMeta(CCommand command);

private:
    QString getGoCmd(int val);
    QString getPageCmd(int val);
    QString getMusicCmd(int val);
    QString getMouseCmd(int val);
    QString getSystemCmd(int val);
    QString getTouchCmd(int val);
    void getScrollCmd(int meta, int val);

    ReState *state;
};



#endif // RE_META_H
