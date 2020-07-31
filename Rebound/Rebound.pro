TEMPLATE = app

QT += qml quick

win32:QT += gamepad

SOURCES += main.cpp \
    backend.cpp \
    re_client.cpp \
    re_exec.cpp

win32:SOURCES += re_server.cpp

RESOURCES += ui.qrc \
    images.qrc \
    fonts.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

HEADERS += \
    backend.h \
    re_client.h \
    re_exec.h

win32:HEADERS += re_server.h
