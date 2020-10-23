
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQuickItem>
#ifdef _WIN32
    #include "re_xbox_w.h"
    #ifdef RE_TEST_EN
    #include "re_client.h"
    #endif
#else
    #include "re_client.h"
    #include "re_native.h"
#endif

//#define NATIBE_MODE

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
    ReXboxW *channel_se;
#ifdef NATIBE_MODE
    channel_se = new ReXboxW(item, 1);
#else
    channel_se = new ReXboxW(item, 0);
#endif

#ifdef RE_TEST_EN
    ReClient *channel_cl;
    channel_cl = new ReClient();
#endif

#elif __linux__
    if (argc > 1) //Run native mode
    {
        ReXboxL *native_cl;
        native_cl = new ReXboxL(item);
    }
    else
    {
        ReClient *channel_cl;
        channel_cl = new ReClient(item);
    }
#endif

    return app.exec();
}

