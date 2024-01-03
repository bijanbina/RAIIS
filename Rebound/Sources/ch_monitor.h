#ifndef CH_MONITOR_H
#define CH_MONITOR_H

#include <QString>
#include <QVector>

#ifdef WIN32
#include <Windows.h>
#endif

typedef struct ChScreen
{
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
} ChScreen;

class ChMonitor
{
public:
    ChMonitor();

    static void init();

    static ChScreen primary;
    static ChScreen secondary;
};

#endif // CH_MONITOR_H
