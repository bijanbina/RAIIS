#include <QCoreApplication>
#include "chaper.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qInfo() << "Service Started";
    chaper *sender = new chaper();
    return a.exec();
}
