TEMPLATE = app

QT += qml quick

win32:QT += gamepad

SOURCES += Sources/main.cpp \
           Sources/backend.cpp \
           Sources/re_chapar.cpp \
           Sources/re_client.cpp \
           Sources/re_state.cpp


win32:SOURCES += Sources/re_server.cpp \
                 Sources/re_xbox_win32.cpp \
                 Sources/re_execw.cpp \
                 Sources/re_xbox_w.cpp

linux:SOURCES += Sources/re_exec.cpp \
                 Sources/re_x11.cpp \
                 Sources/re_xbox_l.cpp

HEADERS += Sources/backend.h \
           Sources/re_chapar.h \
           Sources/re_keycode.h \
           Sources/re_client.h \
           Sources/re_state.h


win32:HEADERS += Sources/re_server.h \
                 Sources/re_xbox_win32.h \
                 Sources/re_execw.h \
                 Sources/re_xbox_w.h

linux:HEADERS += Sources/re_exec.h \
                 Sources/re_x11.h \
                 Sources/re_xbox_l.h

RESOURCES += Qml/ui.qrc \
             Resources/images.qrc \
             Resources/fonts.qrc

OTHER_FILES += Qml/*.qml

linux:LIBS += -lX11 \
              -lXtst

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH += Qml/

