#include "re_status_file.h"

QString re_readStatus()
{
#ifdef WIN32
    ///POLYBAR INTEGRATION
    QString path = MOM_LABEL_DIR;
    path += MOM_LABEL_STATUS;
#else
    QString path = getenv("HOME");
    path += "/.config/polybar/awesomewm/ben_status";
#endif
    QFile file(path);
    QString buffer;

    if( file.open(QIODevice::ReadOnly) )
    {
        buffer = file.readLine();
        buffer.replace('\n', "");
        file.close();
    }

    return buffer;
}

void re_rmStatus()
{
#ifdef WIN32
    QString path = MOM_LABEL_DIR;
    path += MOM_LABEL_STATUS;
#else
    QString path = getenv("HOME");
    path += "/.config/polybar/awesomewm/ben_status";
#endif
    if( QFileInfo::exists(path) )
    {
#ifdef WIN32
        QString cmd = "del ";
#else
        QString cmd = "rm ";
#endif
        cmd += path;

        system(cmd.toStdString().c_str());
    }
}

void re_rmSpex()
{
#ifdef WIN32
    ///POLYBAR INTEGRATION
#else
    QString path = getenv("HOME");
    path += "/.config/polybar/awesomewm/ben_spex";
    if( QFileInfo::exists(path) )
    {
        QString cmd = "rm ";
        cmd += path;

        system(cmd.toStdString().c_str());
    }
#endif
}
