#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQuickItem>
#include "re_client.h"

#ifdef _WIN32
#include <re_server.h>
#endif

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QObject *item = engine.rootObjects().first();
    ReServer *channel_se;
    ReClient *channel_cl;

    updateScreenInfo(item);

    //check if app should start in server
    //or client mode
//    int isServer = RE_CLIENT;
    int isServer = RE_SERVER;
    if (argc > 1)
    {
        isServer = atoi(argv[1]);
    }

#ifdef _WIN32
    channel_se = new ReServer(item);
#elif __linux__
    channel_cl = new ReClient(item);
#endif

    //REMOVE THIS LINE
    channel_cl = new ReClient(item);
    //REMOVE THIS LINE

    return app.exec();
}

