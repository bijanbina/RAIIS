TEMPLATE = app

QT += qml quick

win32:QT += gamepad

# Only uncomment if you wand native mode
QT += gamepad

SOURCES += main.cpp \
           backend.cpp \
           re_win.cpp \
           re_client.cpp

win32:SOURCES += re_server.cpp \
                 re_xbox_win32.cpp
linux:SOURCES += re_exec.cpp \
                 re_native.cpp

RESOURCES += Qml/ui.qrc \
             Resources/images.qrc \
             Resources/fonts.qrc

OTHER_FILES += Qml/*.qml

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH += Qml/

HEADERS += \
    backend.h \
    re_keycode.h \
    re_win.h \
    re_client.h

win32:HEADERS += re_server.h \
                 re_xbox_win32.h
linux:HEADERS += re_exec.h \
                 re_native.h

