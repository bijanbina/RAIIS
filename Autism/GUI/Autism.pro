TEMPLATE = app

QT += qml quick

SOURCES += main.cpp \
    transmission.cpp \
    uihandler.cpp

RESOURCES += ui.qrc \
    images.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

HEADERS += \
    transmission.h \
    uihandler.h
