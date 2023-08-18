#ifndef CH_MONITOR_H
#define CH_MONITOR_H

#include <QObject>
#include <QString>
#include <QVector>

#include <Windows.h>

typedef struct ChScreen
{
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
} ChScreen;

class ChMonitor : public QObject
{
    Q_OBJECT
public:
    explicit ChMonitor(QObject *parent = nullptr);
    ~ChMonitor();

    ChScreen primary;
    ChScreen secondary;
};

#endif // CH_MONITOR_H
