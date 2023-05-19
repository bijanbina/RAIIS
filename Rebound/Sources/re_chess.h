#ifndef RE_CHESS_H
#define RE_CHESS_H

#include <QObject>
#include <QThread>

#include "backend.h"
#include "re_captain.h"

class ReChess : public QObject
{
    Q_OBJECT
public:
    ReChess(ReCaptain *cpt, QObject *parent = NULL);
    ~ReChess();

    void dirs (const QString &arg);
    void nato (const QString &arg);
    void super(const QString &arg); //single shot meta cmd
    void digit(const QString &arg);

private:
    void sendKeyChess(QString text);
    void resetChess();

    QObject  *root;
    ReCaptain *captain;

    int cmd_count;
    int meta_mode;
    QString commands_str; //just for debug purpose
};

#endif // RE_CHESS_H
