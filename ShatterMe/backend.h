#ifndef BACKEND_H
#define BACKEND_H

#include <QDebug>
#include <QString>


#define SHATTER_DEBUG   true

void shatter_debug(QString message);
void shatter_debug(char *message);
char bitreader(char *data, int offset);
short MakeCRC(char *BitString);
QString getStrCommand(QString command);

#endif // BACKEND_H
