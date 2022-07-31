TEMPLATE = app

QT += qml quick dbus core websockets

CONFIG += console

win32:QT += gamepad

SOURCES += Sources/main.cpp \
           Sources/backend.cpp \
           Sources/re_captain.cpp \
           Sources/re_chapar.cpp \
           Sources/re_client.cpp \
           Sources/re_commands.cpp \
           Sources/re_firefox.cpp \
           Sources/re_firefox_ws.cpp \
           Sources/re_lua.cpp \
           Sources/re_meta.cpp \
           Sources/re_meta_go.cpp \
           Sources/re_meta_oc.cpp \
           Sources/re_mouse.cpp \
           Sources/re_preprocessor.cpp \
           Sources/re_qt.cpp \
           Sources/re_state.cpp \
           Sources/re_buttons.cpp \
           Sources/re_directions.cpp \
           Sources/re_laxis.cpp \
           Sources/re_raxis.cpp \
           Sources/re_bumpers.cpp \
           Sources/re_super.cpp

win32:SOURCES += Sources/re_server.cpp \
                 Sources/re_api_w.cpp \
                 Sources/re_channel_w.cpp \
                 Sources/re_keyboard_W.cpp \
                 Sources/re_thread_w.cpp \
                 Sources/re_hardware_w.cpp \
                 Sources/re_admin_win.cpp \
                 Sources/re_win32_virt.cpp \
                 Sources/re_xbox_win32.cpp \
                 Sources/re_xbox_w.cpp

linux:SOURCES += \
                 Sources/re_x11.cpp \
                 Sources/re_xbox_l.cpp  \
                 Sources/re_api_l.cpp \
                 Sources/re_thread_l.cpp \
                 Sources/re_channel_l.cpp \
                 Sources/re_keyboard_l.cpp

HEADERS += Sources/backend.h \
           Sources/re_captain.h \
           Sources/re_chapar.h \
           Sources/re_commands.h \
           Sources/re_config.h \
           Sources/re_firefox.h \
           Sources/re_firefox_ws.h \
           Sources/re_keycode.h \
           Sources/re_client.h \
           Sources/re_lua.h \
           Sources/re_meta.h \
           Sources/re_meta_go.h \
           Sources/re_mouse.h \
           Sources/re_preprocessor.h \
           Sources/re_qt.h \
           Sources/re_state.h \
           Sources/re_buttons.h \
           Sources/re_directions.h \
           Sources/re_laxis.h \
           Sources/re_raxis.h \
           Sources/re_bumpers.h \
           Sources/re_state_const.h \
           Sources/re_super.h

win32:HEADERS += Sources/re_api_w.h \
                 Sources/re_app_w.h \
                 Sources/re_admin_win.h \
                 Sources/re_channel_w.h \
                 Sources/re_keyboard_w.cpp \
                 Sources/re_thread_w.h \
                 Sources/re_server.h \
                 Sources/re_hardware_w.h \
                 Sources/re_win32_virt.h \
                 Sources/re_xbox_win32.h \
                 Sources/re_xbox_w.h

linux:HEADERS += Sources/re_api_l.h \
                 Sources/re_app_l.h \
                 Sources/re_channel_l.h \
                 Sources/re_keyboard_l.h \
                 Sources/re_thread_l.h \
                 Sources/re_x11.h \
                 Sources/re_xbox_l.h

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

win32:LIBS += -L../../Benjamin/PNN/libs \
              -lKernel32 -lUser32 -lole32 \
              -luuid -loleaut32 -loleacc \
              -lDwmapi -lPsapi -lSetupapi \
              -llua54

win32:INCLUDEPATH += ../../Benjamin/PNN/lua

win32:RC_FILE = rebound.rc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH += Qml/

DISTFILES += \
    Rebound.exe.manifest

MOC_DIR = Build/.moc
RCC_DIR = Build/.rcc
OBJECTS_DIR = Build/.obj
UI_DIR = Build/.ui

HEADERS += \
    Sources/re_meta_oc.h

