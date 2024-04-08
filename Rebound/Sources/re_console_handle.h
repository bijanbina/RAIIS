#ifndef RE_CONSOLE_HANDLE_H
#define RE_CONSOLE_HANDLE_H

#include <QObject>
#include <windows.h>

#define RE_CONSOLE_NORML 0
#define RE_CONSOLE_ERROR 1

#define CONSOLE_BUF_SIZE 4096

class ReConsoleHandle: public QObject
{
    Q_OBJECT
public:
    explicit ReConsoleHandle(int fl, QObject *parent = nullptr);
    ~ReConsoleHandle();

    HANDLE handle = NULL;
public slots:
    void readData();

signals:
    void readyData(QString data, int mode);

private:
    int flag;
};

#endif // RE_CONSOLE_HANDLE_H
