#include <QCoreApplication>
#include "chapar.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qInfo() << "Service Started";
    chapar *sender = new chapar();
    
    /*char send_command[100];
    send_command[0] = 0x52;
    send_command[1] = 0x00;
    send_command[2] = 0x1f;
    send_command[3] = 0;
    send_command[4] = 0;
    send_command[5] = 0;
    send_command[6] = 0;
    send_command[7] = MakeCRC(send_command);
    shatter_debug_hex("crc:\t", send_command, PACKET_LEN);
    
    while(true)
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
