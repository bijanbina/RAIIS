#-------------------------------------------------
#
# Project created by QtCreator 2014-10-28T18:13:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GNC


SOURCES += main.cpp\
        mainwindow.cpp\
	calibratewindow.cpp \
        recwindow.cpp \
        calibrateiiwindow.cpp \
        gnccore.cpp

HEADERS  += mainwindow.h\
	calibratewindow.h \
        recwindow.h \
        calibrateiiwindow.h \
        gnccore.h

PKGCONFIG += opencv jsoncpp
CONFIG += link_pkgconfig

INCLUDEPATH      += /usr/include/qwt
#INCLUDEPATH      += /usr/lib/include/qwt
LIBS        += -lqwt -lm -lpthread
QMAKE_CXXFLAGS += -g
#QMAKE_CXXFLAGS += -E
