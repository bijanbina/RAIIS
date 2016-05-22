#include "backend.h"

void shatter_debug(QString message)
{
    if (SHATTER_DEBUG)
    {
        qDebug() << message;
    }
}

void shatter_debug(char *message)
{
    if (SHATTER_DEBUG)
    {
        qDebug() << message;
    }
}
