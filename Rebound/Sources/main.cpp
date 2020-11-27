#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQuickItem>
#include "re_chapar.h"
#define NATIVE_MODE

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:main.qml")));
    QObject *item = engine.rootObjects().first();

#ifdef _WIN32
    //Set NoActivable Flag on UI
    QWindow *window = qobject_cast<QWindow *>(item);
    if(window)
    {
        HWND hwnd = (HWND)window->winId();
        SetWindowLongPtrA(hwnd, GWL_EXSTYLE, WS_EX_NOACTIVATE);
    }

    //Use for lnk resolve
    CoInitialize(NULL);   //<< add
#endif

    QQmlApplicationEngine engineSwitcher;
    engineSwitcher.load(QUrl(QStringLiteral("qrc:ReSwitcher.qml")));
    QObject *itemSwitcher = engineSwitcher.rootObjects().first();


    updateScreenInfo(item);
    //check if app should start in server
    //or client mode

#ifdef NATIVE_MODE
    int isNative = 1;
#ifdef __linux__
    if ( argc>1 )
    {
        QString argv_1 = argv[1]; bool ok;
        int argv_int = argv_1.toInt(&ok);

        if(ok)
        {
            isNative = argv_int;
        }
    }
#endif
#else
    int isNative = 0;
    if ( argc>1 )
    {
        isNative = 1;
    }
#endif
    ReChapar *chaper = new ReChapar(item, itemSwitcher, isNative);

#ifdef RE_TEST_EN
    ReClient *channel_cl;
    channel_cl = new ReClient();
#endif

    return app.exec();
}

