TEMPLATE = app

QT += qml quick

win32:QT += gamepad

SOURCES += main.cpp \
           backend.cpp \
           re_win.cpp \
           re_client.cpp

win32:SOURCES += re_server.cpp
linux:SOURCES += re_exec.cpp

RESOURCES += ui.qrc \
             images.qrc \
             fonts.qrc

OTHER_FILES += \
               Qml/*.qml

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH += Qml/

HEADERS += \
    backend.h \
    re_win.h \
    re_client.h

win32:HEADERS += re_server.h
linux:HEADERS += re_exec.h

