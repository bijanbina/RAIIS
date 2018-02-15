#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <blue_driver.h>
#include "motiond.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QObject *root = engine.rootObjects().first();
    motiond *channel = new motiond(root);

    blue_driver *drv = new blue_driver(channel);


    return app.exec();
}
