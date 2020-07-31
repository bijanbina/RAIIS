TEMPLATE = app

QT += qml quick

win32:QT += gamepad

SOURCES += main.cpp \
    backend.cpp \
    re_client.cpp \
    re_server.cpp \
    re_exec.cpp

RESOURCES += ui.qrc \
    images.qrc \
    fonts.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

HEADERS += \
    backend.h \
    re_client.h \
    re_server.h \
    re_exec.h
