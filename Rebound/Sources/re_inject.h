#ifndef REINJECT_H
#define REINJECT_H

#include <QObject>
#include <Windows.h>

//#define INJ_DLL_ADDRESS "D:\\Work\\bijan\\Benjamin\\PNN\\sag\\Sag.dll"
#define INJ_DLL_ADDRESS "Benjamin/PNN/sag/debug/Sag.dll"

class ReInject : public QObject
{
    Q_OBJECT
public:
    explicit ReInject(QObject *parent = nullptr);
    void inject(int pid);

private:
    HANDLE getDllHandle(int pid, QString path);
    QString getDllPath();
    int isInjected(int pid);

    QVector<int> apps_pid;
};

#endif // REINJECT_H
