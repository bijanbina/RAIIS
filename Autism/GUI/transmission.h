#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QObject>
#include <QVector>
#include <stdio.h>
#include <stdlib.h>
#include <QTimer>

enum ColorButtonID {
    GREEN_BUTTON,
    BLUE_BUTTON,
    RED_BUTTON
};

class Transmission : public QObject
{
    Q_OBJECT

public:
    explicit Transmission(QObject *ui, QObject *parent = 0);
    ~Transmission();
signals:
    void errorConnection();
private slots:
    void connected();
    void start(QString IP);
    int startTransfer(const char* command);
    void displayError(QAbstractSocket::SocketError socketError);

    void set_lamp(int id);
    void change_color(int id);
    void music_random();
    void music_play();
private:
    QTcpSocket tcpClient;
    void tof_on_screen(QString message);

    QVector<QString> stack;
    int code;
    char code_char[4];

    QString message;
    char charBuffer;
    bool isBufferEmpty;
    bool commandMode;
    int commandIndex;
    short commandByte;

    QObject *root;
};

#endif // TRANSMISSION_H
