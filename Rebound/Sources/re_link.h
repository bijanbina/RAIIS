#ifndef RE_LINK_H
#define RE_LINK_H

#include <QDebug>
#include "re_commands.h"
#ifdef WIN32
#include <windows.h>
#endif

#ifdef WIN32
#define RE_PIPE_LINK      "\\\\.\\pipe\\com_binaee_link"
#else
#define RE_PIPE_LINK      "com.binaee.link"
#endif

#define RE_FFGEAR_COUNT 16
#define RE_FFGEAR_DELAY { 100, 50, 25, 10, 10, 5, 5, 5, 5,  5,  \
                          5  ,  5,  5,  5,  5}
#define RE_FFGEAR_STEP  { 1  , 2 ,  3,  4,  5, 6, 7, 8, 9, 20, \
                          25 , 40, 50, 60, 70}

class ReLink
{
public:
    ReLink();
    void connectPipe();
    void sendPipe(const char *data);
    void scrollUp(int speed);
    void scrollDown(int speed);
    void scrollEscape();

    int sc_dir   = 0;  // 0 deactive, other active
    int sc_speed = 5;

private:
    int speed_table[RE_FFGEAR_COUNT] = RE_FFGEAR_DELAY;
    int step_table [RE_FFGEAR_COUNT] = RE_FFGEAR_STEP;

#ifdef WIN32
    HANDLE hPipe;
#endif
};

#endif // RE_LINK_H
