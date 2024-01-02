#ifndef RESTATEOLD_H
#define RESTATEOLD_H

#include <QObject>
#include "backend.h"
#include "re_status_file.h"
#include "re_commands.h"

class ReStateOld : public QObject
{
    Q_OBJECT
public:
    explicit ReStateOld(QObject *parent = nullptr);
    ~ReStateOld();

    void toggleUi(QObject *item);

#ifdef _WIN32
    ReHardwareW *hardware;
#endif

    int  ui_visible;
    int  i_mode;
    int  utube_mode = 0;
};

#endif // RESTATEOLD_H
