#ifndef RESTATE_H
#define RESTATE_H

#include <QObject>
#include <QString>
#include <QQmlProperty>

#ifdef _WIN32
#include "re_api_w.h"
#include "re_hardware_w.h"
#endif
#ifdef __linux__
#include "re_api_l.h"
#endif

typedef struct ReWinSpec
{
    // verify clear on each enumeration to
    int  verify; //verify hwnd still exist
    QString title;
    QString pname;
#ifdef _WIN32
    HWND hWnd;
    IAccessible *pAcc;
#endif
#ifdef __linux__
    long hWnd;
#endif
}ReWinSpec;

class ReState : public QObject
{
    Q_OBJECT
public:
    explicit ReState(QObject *parent = 0);
    void setMode(int mode);
    int getMode();

    void setProcess(QString name);
    void setProcess(int proc);
    int getProcess();
    void updateApp(ReWinSpec active_window);
    void toggleUi(QObject *item);
    void propageteMode(int mode);
    void updateTitles(QObject *item);
    void showSwither(QObject *item);

#ifdef _WIN32
    ReApiW *api;
    ReHardwareW *hardware;
#endif
#ifdef __linux__
    ReApiL *api;
#endif
    int ui_visible;
    int i_mode;
    ReWinSpec app; //Active Window

signals:
    void updateMode();

private:
    int i_proc;
};

#endif // RESTATE_H
