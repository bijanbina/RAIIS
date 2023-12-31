#ifndef RE_META_MOS_H
#define RE_META_MOS_H

#include <QVector>
#include <QThread>

#include "backend.h"
#include "re_state.h"
#include "re_mouse.h"

class ReMetaMos: public QObject
{
    Q_OBJECT
public:
    explicit ReMetaMos(QObject *parent = nullptr);

    void castCode(int val, CCommand *cmd);
    void castMonitor(int val);
    void castScroll(int val);
    void castFirefox(int val, CCommand *cmd);

private:
    ChMonitor *mon;
};

#endif // RE_META_MOS_H
