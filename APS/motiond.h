#ifndef MOTIOND_H
#define MOTIOND_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlProperty>

class motiond : public QObject
{
    Q_OBJECT
public:
    explicit motiond(QObject *ui, QObject *parent = 0);
    void dataready(QByteArray data);

signals:

public slots:

private:

    QObject  *root;
};

#endif // MOTIOND_H
