#include "re_lua.h"
#include <QtDebug>
#include <QDir>
#include <QSettings>
#include "backend.h"


#define WS_SC_PATH "Scripts/Firefox/getWS.sh"

ReLua::ReLua()
{
#ifdef WIN32
    lst = luaL_newstate();
    luaL_openlibs(lst);
    exec("init.lua");
    addRegisteryKeys();
#endif
}

#ifdef WIN32
QString ReLua::exec(const char *path)
{
    QString current_dir = QDir::currentPath();
    QDir::setCurrent(RE_FIREFOX_DIR);

    luaL_loadfile(lst, path);
    lua_pcall(lst, 0, LUA_MULTRET, 0);

    lua_getglobal(lst, "url_list");
    QString output = lua_tostring(lst, -1);

//    qDebug() << "LUA : " << output;
    QDir::setCurrent(current_dir);

    return output;
}
#endif

QStringList ReLua::getWSList()
{
#ifdef WIN32
    QString ws = exec("getWS.lua");
#else
    QString ws = getStrCommand(WS_SC_PATH);
#endif
    QStringList ws_list = ws.split("\n", QString::SkipEmptyParts);
    return ws_list;
}

ReLua::~ReLua()
{
#ifdef WIN32
    lua_close(lst);
#endif
}

#ifdef WIN32
void ReLua::addRegisteryKeys()
{
    QString reg = "HKEY_LOCAL_MACHINE\\SOFTWARE\\"
                  "Mozilla\\NativeMessagingHosts\\link";
    if( regExist(reg)==0 )
    {
        QString json_path = QDir::currentPath();
        json_path.replace("/", QDir::separator());
        QStringList path_split = json_path.split(QDir::separator(),
                                                 Qt::SkipEmptyParts);
        path_split.removeLast(); // remove Rebound
        path_split.removeLast(); // remove RAIIS
        json_path = path_split.join(QDir::separator());
        json_path += "\\Benjamin\\Link\\Resources\\manifest.json";
        QSettings settings(reg, QSettings::NativeFormat);
        settings.setValue("Default", json_path);
    }

    reg = "HKLM\\SOFTWARE\\Policies\\Mozilla\\Firefox";
    if( regExist(reg)==0 )
    {
        QSettings settings(reg, QSettings::NativeFormat);
        settings.setValue("DisableAppUpdate", 1);
    }

    reg = "HKCU\\Control Panel\\Desktop";
    if( regExist(reg)==0 )
    {
        QSettings settings(reg, QSettings::NativeFormat);
        settings.setValue("AutoEndTasks ", "1");
    }
}

int ReLua::regExist(QString path)
{
    HKEY hKey;
    QStringList path_split = path.split(QDir::separator(),
                                        Qt::SkipEmptyParts);
    path_split.removeFirst();
    QString path_noHKLM = path_split.join(QDir::separator());
    long reg_exist = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
            (LPCTSTR)(path_noHKLM.toStdString().c_str()),
            0, KEY_READ, &hKey);
    if( reg_exist!=ERROR_SUCCESS )
    {
        return false;
    }
    return true;
}

#endif
