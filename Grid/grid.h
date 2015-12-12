#ifndef GRID_H
#define GRID_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QObject>
#include <QTimer>
#include <QtSerialPort/QSerialPort>

#define WRITE_BUFFER_LENGTH 100
#define X_MAX 150
#define Y_MAX 150

class Grid : public QObject
{
    Q_OBJECT

public:
    explicit Grid(QObject *parent = 0);
    ~Grid();
signals:
    void errorConnection();
private slots:
    void pressedSlot(qreal x, qreal y);

    void releaseSlot(qreal x, qreal y);

    void on_dataReady();

private:
    QSerialPort *port = new QSerialPort;
    QString readData;
};

#endif // TRANSMISSION_H
