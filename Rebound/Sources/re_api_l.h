#ifndef ReApiL_H
#define ReApiL_H

#include <QObject>
#include <QtDebug>
#include <QStringList>

#define RE_MODE_APPLICATION 1
#define RE_MODE_SWITCH      2
#define RE_MODE_MAIN        3
#define RE_MODE_READING     4
#define RE_MODE_FIREFOX     5
#define RE_MODE_SPOTIFY     6
#define RE_MODE_HIDDEN      7

#define RE_PROC_UNKNOWN     1
#define RE_PROC_SPOTIFY     1
#define RE_PROC_FIREFOX     2
#define RE_PROC_NAUTILUS    3
#define RE_PROC_READING     4
#define RE_PROC_QT          5
#define RE_PROC_GEDIT       6
#define RE_PROC_OVERVIEW    7
#define RE_PROC_TELEGRAM    8

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
    void setActiveWindow(long hWnd);
    void openApp(int appid);
    QString getLinkPath(QString path);

    QStringList wins_title;
    QStringList elems_name;

private slots:

private:
};

#endif // ReApiL_H
