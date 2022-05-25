#ifndef ReApiL_H
#define ReApiL_H

#include <QObject>
#include <QtDebug>
#include <QStringList>
#include <X11/Xlib.h>
#include "re_state_const.h"

class ReApiL : public QObject
{
    Q_OBJECT
public:
    explicit ReApiL(QObject *parent = nullptr);
    QString getPNameA();
    long getPid();
    QString getPName(long pid);
    QString getAccName(long childId);
    QString getWinTitle(int index);
    QString getElemName(int index);
    void setActiveWindow(Window win);
    void setDisplay(Display *display);
    void openApp(int appid);
    QString getLinkPath(QString path);

    QStringList wins_title;
    QStringList elems_name;

private slots:

private:
    Display *disp;
};

#endif // ReApiL_H
