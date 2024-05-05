#ifndef RE_CONSOLE_H
#define RE_CONSOLE_H

#include <QObject>
#include <QThread>
#include <windows.h>
#include "re_console_handle.h"

class ReConsole : public QObject
{
    Q_OBJECT
public:
    explicit ReConsole(QObject *parent = nullptr);
    ~ReConsole();

    void stopApp();

    QVector<QString> commands;

public slots:
    void startConsole(QString wsl_path);
    void readyData(QString data, int mode);

signals:
    void startRead();
    void finished();
    void trainFailed();

private:
    void processLine(QString line);
    void checkModel();
    void CreateCmdProcess();
    QString capitalize(QString str);

    HANDLE proc_in_h  = NULL;
    HANDLE proc_out_h = NULL;
    HANDLE proc_err_h = NULL;
    HANDLE handle_in  = NULL;
    PROCESS_INFORMATION piProcInfo;

    ReConsoleHandle *std_err;
    QThread *err_thread;
    ReConsoleHandle *std_out;
    QThread *out_thread;

    int is_ready;
    QString last_line;
    QStringList c_exception; // capitalization exceptions
};

#endif // RE_CONSOLE_H
