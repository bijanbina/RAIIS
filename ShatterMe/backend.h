#ifndef BACKEND_H
#define BACKEND_H

#include <QDebug>
#include <QString>


#define SHATTER_DEBUG   true

void shatter_debug(QString message);
void shatter_debug(char *message);

#endif // BACKEND_H
