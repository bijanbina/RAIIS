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
    QObject::connect(item, SIGNAL(change_color(int)), &channel, SLOT(change_color(int)));
    QObject::connect(item, SIGNAL(music_random()), &channel, SLOT(music_random()));
    QObject::connect(item, SIGNAL(music_play()), &channel, SLOT(music_play()));

    return app.exec();
}

