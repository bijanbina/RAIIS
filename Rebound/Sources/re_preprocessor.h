#ifndef RE_PREPROCESSOR_H_L
#define RE_PREPROCESSOR_H_L

#include <QObject>
#include <QThread>

#include "backend.h"
#include "re_captain.h"

class RePreProcessor : public QObject
{
    Q_OBJECT
public:
    RePreProcessor(ReCaptain *cpt, QObject *parent = NULL);

    ~RePreProcessor();

public slots:
    void dirs (const QString &arg);
    void nato (const QString &arg);
    void meta (const QString &arg);
    void apps (const QString &arg);
    void type (const QString &arg); //No Repeat on LastCmd
    void spex (const QString &arg); //special
    void super(const QString &arg); //single shot meta cmd
    void digit(const QString &arg);
    void modifier(const QString &arg);
    void debug(const QString &arg);
    void execute();

private:
    void handleLastRepeatable(int input);

    QObject  *root;
    ReCaptain *captain;
    int special_c; //count of special

    QVector<CCommand> cmd_buf;
    QString commands_str; //just for debug purpose
};



#endif // RE_PREPROCESSOR_H_L
