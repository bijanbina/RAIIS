#ifndef REINJECT_H
#define REINJECT_H

#include <QObject>
#include <Windows.h>

//#define INJ_DLL_ADDRESS "D:\\Work\\bijan\\Benjamin\\PNN\\sag\\Sag.dll"
#define INJ_DLL_ADDRESS "Benjamin/PNN/sag/debug/Sag.dll"

class ReInject
{
public:
    explicit ReInject();
    static void inject(int pid);

    static HANDLE getDllHandle(int pid, QString path);
    static QString getDllPath();
    static int isInjected(int pid);

    static QVector<int> apps_pid;
};

#endif // REINJECT_H
