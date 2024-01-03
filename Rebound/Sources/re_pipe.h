#ifndef RE_PIPE_H
#define RE_PIPE_H

#include <QDebug>
#include <windows.h>
#include "backend.h"

class RePipe
{
public:
    RePipe();

    static void init();

    static void sendChess(const char *data);
    static void sendMom(const char *data);
    static HANDLE connectPipe(const char *pipe_name);

    static HANDLE pipe_chess;
    static HANDLE pipe_mom;
};

#endif // RE_PIPE_H
