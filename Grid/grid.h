#ifndef GRID_H
#define GRID_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QObject>
#include <QTimer>
#include <QtSerialPort/QSerialPort>

#define WRITE_BUFFER_LENGTH 100
#define X_MAX               147
#define Y_MAX               100
#define SCREEN_WIDTH        70
#define SCREEN_HEIGHT       50

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
    qreal x_last,y_last;
};

#endif // TRANSMISSION_H
