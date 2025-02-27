#ifndef RE_CHAPAR_H
#define RE_CHAPAR_H

#include <QObject>
#include <QTimer>

#ifdef WIN32
    #include "re_xbox_w.h"
    #include "re_window_w.h"
    #include "re_channel_w.h"
    #include "re_link_rx.h"
    #ifdef RE_TEST_EN
        #include "re_client.h"
    #endif
#endif

#ifdef __linux__
    #include "re_channel_l.h"
    #include "re_client.h"
    #include "re_xbox_l.h"
    #include "re_thread_l.h"
    #include "re_api_l.h"
#endif

#include <thread>         // std::thread
#include "re_captain.h"
#include "re_bumpers.h"
#include "re_buttons.h"
#include "re_directions.h"
#include "re_laxis.h"
#include "re_raxis.h"
#include "re_state.h"
#include "re_remote.h"

typedef struct RePage
{
    QString x_action;
    QString y_action;
    QString a_action;
    QString b_action;
    QString m_action;
    QString s_action;
    QString r1_action;
    QString r2_action;
    QString l1_action;
    QString l2_action;
    QString lau_action; //left axis up
    QString lad_action; //left axis down
    QString lal_action; //left axis left
    QString lar_action; //left axis right
    QString rau_action; //right axis up
    QString rad_action; //right axis down
    QString ral_action; //right axis left
    QString rar_action; //right axis right
    QString left_action;
    QString right_action;
    QString up_action;
    QString down_action;
    QString axis_state;
}RePage;

class ReChapar : public QObject
{
    Q_OBJECT
public:
    explicit ReChapar(QObject *item, QObject *switcher, int isNative,
                      QObject *parent = nullptr);

    void setPage(RePage page);

signals:
    void startChannel();

private slots:
    void requstSuspend();

private:
    QObject      *ui;
    QObject      *uiSwitcher;
    ReStateOld   *state_old;
    ReBumpers    *bumpers;
    ReButtons    *buttons;
    ReDirections *directions;
    ReLAxis      *laxis;
    ReRAxis      *raxis;

    ReCaptain *captain;
    ReRemote  *remote;
#ifdef _WIN32
    ReXboxW    *controller;
    ReWindowW  *window;
    QThread    *window_thread;

    ReChannelW *channel;
    QThread    *channel_thread;

    ReLinkRx   *link_rx;
    QThread    *link_thread;
#else
    ReXboxL *controller;
    ReChannelL *channel;
    std::thread *api_thread;
    threadStruct *thread_data;
#endif
};

#endif // RE_CHAPAR_H
