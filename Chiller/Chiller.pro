QT += network widgets

HEADERS       = dialog.h
SOURCES       = dialog.cpp \
                main.cpp

HEADERS += \
    transmission.h

QMAKE_CXXFLAGS +=-I. -DNETSNMP_ENABLE_IPV6 -fno-strict-aliasing -march=x86-64 -mtune=generic \
                 -O2 -pipe -fstack-protector-strong \
                 --param=ssp-buffer-size=4 -Ulinux -Dlinux=linux -D_REENTRANT \
                 -D_GNU_SOURCE -fwrapv -fno-strict-aliasing -pipe -fstack-protector-strong \
                 -I/usr/local/include -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 \
                 -I/usr/lib/perl5/core_perl/CORE -I/usr/include/libnl3 \
                 -D_FORTIFY_SOURCE=2 -I. -I/usr/include -fPIC -shared
#INCLUDEPATH      += /usr/lib/include/qwt
LIBS        += -Wl,-O1,--sort-common,--as-needed,-z,relro \
                -L/usr/lib -lnetsnmpmibs -lpci -ldl -lnetsnmpagent \
                -Wl,-E -Wl,-rpath,/usr/lib/perl5/core_perl/CORE \
                -lnetsnmp -lcrypto -lnl-3 -lm \
                -Wl,-O1,--sort-common,--as-needed,-z,relro \
                -L/usr/lib -lnetsnmp -lcrypto -lnl-3 -lm

# install
target.path = $$[QT_INSTALL_EXAMPLES]/network/loopback
INSTALLS += target
