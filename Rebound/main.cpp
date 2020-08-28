
#ifdef _WIN32
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQuickItem>
#include <re_server.h>
#else
#include <QCoreApplication>
#include "re_client.h"
#endif

#ifdef RE_TEST_EN
#include "re_client.h"
#endif

int main(int argc, char *argv[])
{

#ifdef _WIN32
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:main.qml")));
    QObject *item = engine.rootObjects().first();
    updateScreenInfo(item);
#else
    QCoreApplication app(argc, argv);
#endif

    //check if app should start in server
    //or client mode
//    int isServer = RE_CLIENT;
    int isServer = RE_SERVER;
    if (argc > 1)
    {
        isServer = atoi(argv[1]);
    }

#ifdef _WIN32
    ReServer *channel_se;
    channel_se = new ReServer(item);
#elif __linux__
    ReClient *channel_cl;
    channel_cl = new ReClient();
#endif

#ifdef RE_TEST_EN
    ReClient *channel_cl;
    channel_cl = new ReClient();
#endif

    return app.exec();
}

