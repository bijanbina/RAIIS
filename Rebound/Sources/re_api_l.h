#ifndef ReApiL_H
#define ReApiL_H

#include <QObject>
#include <QtDebug>
#include <QStringList>
#include <X11/Xlib.h>

#define RE_MODE_APPLICATION 1
#define RE_MODE_SWITCH      2
#define RE_MODE_MAIN        3
#define RE_MODE_READING     4
#define RE_MODE_FIREFOX     5
#define RE_MODE_SPOTIFY     6
#define RE_MODE_HIDDEN      7

#define RE_WIN_UNKNOWN     1
#define RE_WIN_SPOTIFY     1
#define RE_WIN_FIREFOX     2
#define RE_WIN_EXPLORER    3
#define RE_WIN_READING     4
#define RE_WIN_QT          5
#define RE_WIN_GEDIT       6
#define RE_WIN_OVERVIEW    7
#define RE_WIN_TELEGRAM    8
#define RE_WIN_TEXTEDITOR  9

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
