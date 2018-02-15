#ifndef MOTIOND_H
#define MOTIOND_H

#include <QObject>

class motiond : public QObject
{
    Q_OBJECT
public:
    explicit motiond(QObject *parent = 0);

signals:

slots:
    void dataready

public slots:
};

#endif // MOTIOND_H
