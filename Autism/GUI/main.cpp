#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <transmission.h>
#include <QQuickView>
#include <QQuickItem>
#include "uihandler.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QObject *item = engine.rootObjects().first();
    UiHandler *handler = new UiHandler(item);

    Transmission channel(item);
    QObject::connect(item, SIGNAL(set_lamp(int)), &channel, SLOT(set_lamp(int)));
    QObject::connect(item, SIGNAL(change_color(int,int)), &channel, SLOT(change_color(int,int)));
    QObject::connect(item, SIGNAL(music_random()), &channel, SLOT(music_random()));
    QObject::connect(item, SIGNAL(music_play()), &channel, SLOT(music_play()));
    QObject::connect(item, SIGNAL(music_stop()), &channel, SLOT(music_stop()));
    QObject::connect(item, SIGNAL(light_off()), &channel, SLOT(light_off()));
    QObject::connect(item, SIGNAL(music_play()), &channel, SLOT(music_play()));
    QObject::connect(item, SIGNAL(light_on()), &channel, SLOT(light_on()));
    QObject::connect(item, SIGNAL(rainbow()), &channel, SLOT(rainbow()));

    return app.exec();
}

