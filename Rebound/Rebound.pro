TEMPLATE = app

QT += qml quick

win32:QT += gamepad

SOURCES += main.cpp \
           backend.cpp \
           re_win.cpp

win32:SOURCES += re_server.cpp
linux:SOURCES += re_exec.cpp \
                 re_client.cpp

RESOURCES += ui.qrc \
    images.qrc \
    fonts.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

HEADERS += \
    backend.h \
    re_win.h

win32:HEADERS += re_server.h
linux:HEADERS += re_exec.h \
                 re_client.h

