
#include "re_client.h"

#ifdef _WIN32
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQuickItem>
#include <re_server.h>
#else
#include <QCoreApplication>
#endif

int main(int argc, char *argv[])
{

#ifdef _WIN32
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QObject *item = engine.rootObjects().first();
    ReServer *channel_se;
    updateScreenInfo(item);
#else
    QCoreApplication app(argc, argv);
#endif
    ReClient *channel_cl;

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
    channel_cl = new ReClient();
#endif

    //REMOVE THIS LINE
    // channel_cl = new ReClient();
    //REMOVE THIS LINE

    return app.exec();
}

