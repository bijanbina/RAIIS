
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQuickItem>
#ifdef _WIN32
    #include "re_win.h"
    #ifdef RE_TEST_EN
    #include "re_client.h"
    #endif
#else
    #include "re_client.h"
    #include "re_native.h"
#endif

#define NATIBE_MODE

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:main.qml")));
    QObject *item = engine.rootObjects().first();
    updateScreenInfo(item);

    //check if app should start in server
    //or client mode

#ifdef _WIN32
    ReWin *channel_se;
#ifdef NATIBE_MODE
    channel_se = new ReWin(item, 1);
#else
    channel_se = new ReWin(item, 0);
#endif

#ifdef RE_TEST_EN
    ReClient *channel_cl;
    channel_cl = new ReClient();
#endif

#elif __linux__
    if (argc > 1) //Run native mode
    {
        ReNative *native_cl;
        native_cl = new ReNative(item);
    }
    else
    {
        ReClient *channel_cl;
        channel_cl = new ReClient(item);
    }
#endif

    return app.exec();
}

