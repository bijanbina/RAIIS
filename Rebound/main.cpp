#include <QCoreApplication>
#include "re_client.h"

#ifdef _WIN32
#include <re_server.h>
#endif

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    ReClient *channel_cl;

    //check if app should start in server
    //or client mode
//    int isServer = RE_CLIENT;
    int isServer = RE_SERVER;
    if (argc > 1)
    {
        isServer = atoi(argv[1]);
    }

#ifdef _WIN32
    ReServer *channel_se;
    channel_se = new ReServer(item);
#elif __linux__
    channel_cl = new ReClient();
#endif

    //REMOVE THIS LINE
    // channel_cl = new ReClient();
    //REMOVE THIS LINE

    return app.exec();
}

