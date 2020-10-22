#ifndef RECHAPAR_H
#define RECHAPAR_H

#include <QObject>

#define RE_MODE_APPLICATION 1
#define RE_MODE_SWITCH      2
#define RE_MODE_MAIN        3
#define RE_MODE_READING     4
#define RE_MODE_FIREFOX     5


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
    explicit ReChapar(QObject *item, QObject *parent = nullptr);

    void setPage(RePage page);
    void setMode(int mode);

signals:

private:
    QObject *ui;

};

#endif // RECHAPAR_H
