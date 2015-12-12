#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <grid.h>
#include <QQuickView>
#include <QQuickItem>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QObject *item = engine.rootObjects().first();
    Grid ui_grid;
    QObject::connect(item, SIGNAL(mouseReleased(qreal , qreal)), &ui_grid, SLOT(releaseSlot(qreal,qreal)));
    QObject::connect(item, SIGNAL(mousePressed(qreal , qreal)), &ui_grid, SLOT(pressedSlot(qreal,qreal)));

    return app.exec();
}

