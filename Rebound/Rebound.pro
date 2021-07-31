TEMPLATE = app

QT += qml quick dbus

CONFIG += console

win32:QT += gamepad

SOURCES += Sources/main.cpp \
           Sources/backend.cpp \
           Sources/re_chapar.cpp \
           Sources/re_client.cpp \
           Sources/re_state.cpp \
           Sources/re_buttons.cpp \
           Sources/re_directions.cpp \
           Sources/re_laxis.cpp \
           Sources/re_raxis.cpp \
           Sources/re_bumpers.cpp

win32:SOURCES += Sources/re_server.cpp \
                 Sources/re_xbox_win32.cpp \
                 Sources/re_xbox_w.cpp \
                 Sources/re_api_w.cpp \
                 Sources/re_thread_w.cpp \
                 Sources/re_hardware_w.cpp \
                 Sources/re_admin_win.cpp

linux:SOURCES += \
                 Sources/re_x11.cpp \
                 Sources/re_xbox_l.cpp  \
                 Sources/re_api_l.cpp \
                 Sources/re_thread_l.cpp \
                 Sources/re_channel_l.cpp \
                 Sources/re_captain_l.cpp \
                 Sources/re_meta_l.cpp

HEADERS += Sources/backend.h \
           Sources/re_chapar.h \
           Sources/re_keycode.h \
           Sources/re_client.h \
           Sources/re_state.h \
           Sources/re_buttons.h \
           Sources/re_directions.h \
           Sources/re_laxis.h \
           Sources/re_raxis.h \
           Sources/re_bumpers.h

win32:HEADERS += Sources/re_server.h \
                 Sources/re_xbox_win32.h \
                 Sources/re_xbox_w.h \
                 Sources/re_api_w.h \
                 Sources/re_thread_w.h \
                 Sources/re_admin_win.h \
                 Sources/re_hardware_w.h

linux:HEADERS += \
                 Sources/re_x11.h \
                 Sources/re_xbox_l.h \
                 Sources/re_api_l.h \
                 Sources/re_thread_l.h \
                 Sources/re_channel_l.h \
                 Sources/re_captain_l.h \
                 Sources/re_meta_l.h

RESOURCES += Qml/ui.qrc \
             Resources/images.qrc \
             Resources/fonts.qrc

OTHER_FILES += Qml/*.qml


linux:INCLUDEPATH += /usr/include/glib-2.0 \
                     /usr/lib/glib-2.0/include

linux:LIBS += -lX11 \
              -lgio-2.0 \
              -lgobject-2.0 \
              -lglib-2.0

win32:LIBS += -lKernel32 \
              -lUser32 \
              -lole32 \
              -luuid \
              -loleaut32 \
              -loleacc \
              -lDwmapi \
              -lPsapi \
              -lSetupapi

win32:RC_FILE = rebound.rc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH += Qml/

DISTFILES += \
    Rebound.exe.manifest

MOC_DIR = Build/.moc
RCC_DIR = Build/.rcc
OBJECTS_DIR = Build/.obj
UI_DIR = Build/.ui

