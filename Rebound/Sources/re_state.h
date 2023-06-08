#ifndef RE_STATE_H
#define RE_STATE_H

#ifdef __linux__
#endif

#include <QObject>
#include <QString>
#include <QQmlProperty>
#include <QFileInfo>
#include "backend.h"
#include "re_firefox.h"
#include "re_commands.h"
#include "re_status_file.h"

class ReState : public QObject
{
    Q_OBJECT
public:
    explicit ReState(QObject *parent = 0);
    ~ReState();

    void readStatusFile();

    void updateApp(ReWindow active_window);
    void toggleUi(QObject *item);

    void goToSleep();
    void goToDictate();
    void wakeUp();
    bool isSleep();
    void enScroll(int dir, int speed);
    bool isEscape(CCommand command);
    void resetState();
    void sendPipe(const char *data);

#ifdef _WIN32
    void connectChessPipe();

    ReApi *api;
    ReHardwareW *hardware;
    HANDLE hPipe;
#endif
    int  ui_visible;
    int  i_mode;
    bool sleep_state = 0;
    bool dictate_state = 0;
    int  ch_count  = 0; //Chess Count
    int  utube_mode  = 0;
    ReWindow app; //Active Window
    CCommand last_cmd;
    ReFirefox *fl;

signals:
    void updateMode();
};

#endif // RE_STATE_H
