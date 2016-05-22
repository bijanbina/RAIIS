#include <QCoreApplication>
#include "chapar.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qInfo() << "Service Started";
    chapar *sender = new chapar();
    /*while(true)
    {
        QString command = "/usr/local/bin/snmpset -v2c -c tutset localhost NET-SNMP-TUTORIAL-MIB::nstAgentModuleObject.0 = ";
        command.append(QString("%1").arg(12));

        //temp
        //humedity
        //setpoint

        qInfo() << QString("run %1").arg(command);
        getStrCommand(command);
    }*/
    return a.exec();
}
