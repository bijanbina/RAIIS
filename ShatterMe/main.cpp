#include <QCoreApplication>
#include "chaper.h"

QString getStrCommand(QString command)
{
    FILE *fp;
    QString returnData;
    char path[1035];

    /* Open the command for reading. */
    fp = popen(command.toStdString().c_str(), "r");

    if (fp == NULL) {
      printf("Failed to run command\n" );
      return returnData;
    }

    /* Read the output a line at a time - output it. */
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
      returnData = QString(path);
    }

    returnData.remove('\n');

    /* close */
    pclose(fp);
    return returnData;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qInfo() << "Service Started";
    chaper *sender = new chaper();
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
