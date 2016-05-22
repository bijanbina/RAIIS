#-------------------------------------------------
#
# Project created by QtCreator 2016-05-20T11:16:56
#
#-------------------------------------------------

QT       += core \
            serialport

QT       -= gui

TARGET = ShatterMe
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    chapar.cpp \
    backend.cpp

HEADERS += \
    backend.h \
    chapar.h
