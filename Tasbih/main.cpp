#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <transmission.h>
#include <QQuickView>
#include <QQuickItem>
#include "backend.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QObject *item = engine.rootObjects().first();

    updateScreenInfo(item);

    Transmission channel(item);

    return app.exec();
}

