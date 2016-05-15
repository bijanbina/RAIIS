TEMPLATE = app

QT += qml quick

SOURCES += main.cpp \
    transmission.cpp

RESOURCES += ui.qrc \
    images.qrc \
    fonts.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

HEADERS += \
    transmission.h
