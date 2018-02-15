TEMPLATE = app

QT += qml quick bluetooth
CONFIG += c++11

SOURCES += main.cpp \
    blue_driver.cpp \
    motiond.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    blue_driver.h \
    motiond.h
