
#ifdef _WIN32
    #include <QGuiApplication>
    #include <QQmlApplicationEngine>
    #include <QQuickView>
    #include <QQuickItem>
    #include "re_server.h"
    #ifdef RE_TEST_EN
    #include "re_client.h"
    #endif
#else
    #include <QCoreApplication>
    #include "re_client.h"
    #include "re_native.h"
#endif


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
    ReServer *channel_se;
    channel_se = new ReServer(item);

#ifdef RE_TEST_EN
    ReClient *channel_cl;
    channel_cl = new ReClient();
#endif

#elif __linux__
    if (argc > 1) //Run native mode
    {
        ReNative *native_cl;
        native_cl = new ReNative;
        native_cl->loop();
    }
    else
    {
        ReClient *channel_cl;
        channel_cl = new ReClient();
    }
#endif


    return app.exec();
}

