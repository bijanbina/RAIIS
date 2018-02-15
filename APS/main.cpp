#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <blue_driver.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    blue_driver *drv = new blue_driver();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
