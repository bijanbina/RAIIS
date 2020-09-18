TEMPLATE = app

QT += qml quick

win32:QT += gamepad

# Only uncomment if you wand native mode
QT += gamepad

SOURCES += Sources/main.cpp \
           Sources/backend.cpp \
           Sources/re_win.cpp \
           Sources/re_client.cpp

win32:SOURCES += Sources/re_server.cpp \
                 Sources/re_xbox_win32.cpp
linux:SOURCES += Sources/re_exec.cpp \
                 Sources/re_native.cpp \
                 Sources/re_x11.cpp

HEADERS += \
    Sources/backend.h \
    Sources/re_keycode.h \
    Sources/re_win.h \
    Sources/re_client.h

win32:HEADERS += Sources/re_server.h \
                 Sources/re_xbox_win32.h
linux:HEADERS += Sources/re_exec.h \
                 Sources/re_native.h \
                 Sources/re_x11.h

RESOURCES += Qml/ui.qrc \
             Resources/images.qrc \
             Resources/fonts.qrc

OTHER_FILES += Qml/*.qml

linux:LIBS += -lX11 \
              -lXtst

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH += Qml/

