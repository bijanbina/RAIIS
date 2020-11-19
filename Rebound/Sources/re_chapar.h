#ifndef RECHAPAR_H
#define RECHAPAR_H

#include <QObject>
#include <thread>         // std::thread
#include <QTimer>
#include "re_state.h"
#include "re_bumpers.h"
#include "re_buttons.h"
#include "re_directions.h"
#include "re_laxis.h"
#include "re_raxis.h"

#ifdef _WIN32
    #include "re_xbox_w.h"
    #include "re_thread_w.h"
    #ifdef RE_TEST_EN
    #include "re_client.h"
    #endif
#else
    #include "re_client.h"
    #include "re_xbox_l.h"
#endif

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
    explicit ReChapar(QObject *item, QObject *switcher, int isNative, QObject *parent = nullptr);

    void setPage(RePage page);
    void setMode(int mode);


signals:

private slots:
    void updateMode();
    void updateTitles(QStringList titles);
    void switchWindow(int activeProcessId);

private:
    QObject      *ui;
    QObject      *uiSwitcher;
    ReState      *state;
    ReBumpers    *bumpers;
    ReButtons    *buttons;
    ReDirections *directions;
    ReLAxis      *laxis;
    ReRAxis      *raxis;

#ifdef _WIN32
    ReXboxW *controller;
    std::thread *api_thread;
    QTimer *sync_thread_timer;
    threadStruct *thread_data;
#else
    ReXboxL *controller;
#endif
};

#endif // RECHAPAR_H
