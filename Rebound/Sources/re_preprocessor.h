#ifndef RE_PREPROCESSOR_H_L
#define RE_PREPROCESSOR_H_L

#include <QObject>
#include <QThread>

#include "backend.h"
#include "re_captain_l.h"

class RePreProcessor : public QObject
{
    Q_OBJECT
public:
    RePreProcessor(ReCaptainL *cpt, QObject *ui, QObject *parent = NULL);

    ~RePreProcessor();

public slots:
    void dirs (QString &arg);
    void nato (QString &arg);
    void meta (QString &arg);
    void apps (QString &arg);
    void type (QString &arg); //No Repeat on LastCmd
    void spex (QString &arg); //special
    void super(QString &arg); //single shot meta cmd
    void digit(QString &arg);
    void modifier(QString &arg);
    void debug(QString &arg);
    void execute();

private:
    void handleLastRepeatable(int input);

    QObject  *root;
    ReCaptainL *captain;
    int special_c; //count of special

    QVector<CCommand> cmd_buf;
    QString commands_str; //just for debug purpose
};



#endif // RE_PREPROCESSOR_H_L
