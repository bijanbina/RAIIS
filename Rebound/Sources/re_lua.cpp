#include "re_lua.h"
#include <QtDebug>
#include <QDir>
#include <QSettings>
#include "backend.h"

#define WS_SC_PATH "Scripts/Firefox/getWS.sh"

ReLua::ReLua()
{
}

void ReLua::init()
{
#ifdef WIN32
    addRegisteryKeys();
#endif
    exec("init.lua");
    registerBenjFox();
}

QString ReLua::exec(const char *path)
{
    lua_State *lst = luaL_newstate();
    luaL_openlibs(lst);

    QString output;
    QString current_dir = QDir::currentPath();
#ifdef WIN32
    QString ff_path = RE_FIREFOX_DIR;
    ff_path.replace("/", QDir::separator());
    QDir::setCurrent(ff_path);

    luaL_loadfile(lst, path);
    lua_pcall(lst, 0, LUA_MULTRET, 0);

    lua_getglobal(lst, "url_list");
    output = lua_tostring(lst, -1);

//    qDebug() << "LUA : " << output;
#else
    QDir::setCurrent(RE_FIREFOX_DIR);
    system("lua init.lua");
#endif
    QDir::setCurrent(current_dir);

    return output;
}

#ifdef __linux__
void ReLua::patchJson()
{
    QString in_path = QDir::currentPath();
    in_path += "/../..";
    in_path += "/Benjamin/Link/Resources/linux.json";
    in_path.replace("/", QDir::separator());

    QString link_path = QDir::currentPath();
    link_path += "/../..";
    link_path += "/Benjamin/Link/Link";
    link_path.replace("/", QDir::separator());

    QFile json_file(in_path);

    if( !json_file.open(QFile::ReadOnly) )
    {
        qDebug() << "Error 123: cannot open" << in_path;
    }

    QString json_data = json_file.readAll();
    json_file.close();

    QStringList json_lines = json_data.split("\n", Qt::SkipEmptyParts);
    json_lines[3] = "  \"path\": \"";
    json_lines[3] += link_path + "\",";
    json_data = json_lines.join("\n");

    QString output_path = QDir::currentPath();
    output_path += "/../..";
    output_path += "/Benjamin/Link/Resources/link.json";
    output_path.replace("/", QDir::separator());

    QFile output_file(output_path);
    if( !output_file.open(QFile::WriteOnly) )
    {
        qDebug() << "Error 321: cannot open" << output_path;
    }

    output_file.write(json_data.toStdString().c_str());
    output_file.close();
}
#endif

void ReLua::registerBenjFox()
{
    QString json_path = QDir::currentPath();
    json_path += "/../..";
    json_path.replace("/", QDir::separator());
#ifdef WIN32
    json_path += "\\Benjamin\\Link\\Resources\\manifest.json";
    QString reg = "HKLM\\SOFTWARE\\"
                  "Mozilla\\NativeMessagingHosts\\link";
    QString key = "Default";
    QSettings settings(reg, QSettings::NativeFormat);
    settings.setValue(key, json_path);
#else
    json_path += "/Benjamin/Link/Resources/link.json";
    patchJson();
    QStringList paths = {"native-messaging-hosts/", "managed-storage/",
                         "pkcs11-modules/"};
    int len = paths.length();
    for( int i=0 ; i<len ; i++ )
    {
        QString cmd = "mkdir -p ~/.mozilla/" + paths[i];
        system(cmd.toStdString().c_str());
        cmd = "cp " + json_path + " ~/.mozilla/" + paths[i];
        system(cmd.toStdString().c_str());
    }
#endif
}

#ifdef WIN32
void ReLua::addRegisteryKeys()
{
    //disable firefox autoupdate
    QString reg = "HKLM\\SOFTWARE\\Policies\\Mozilla\\Firefox";
    QString key = "DisableAppUpdate";
    QSettings ff_setting(reg, QSettings::NativeFormat);
    ff_setting.setValue(key, 1);

    // End Tasks on Shutdow
    reg = "HKCU\\Control Panel\\Desktop";
    key = "AutoEndTasks";
    QSettings sh_setting(reg, QSettings::NativeFormat);
    sh_setting.setValue(key, 1);

    // allow running ps1 (powershell) instead of oppening in
    // notepad
    reg = "HKCR\\Microsoft.PowerShellScript.1\\Shell";
    key = "Default";
    QSettings ps_setting(reg, QSettings::NativeFormat);
    ps_setting.setValue(key, 0); // execute
}

int ReLua::regExist(QString path, QString key)
{
    QStringList path_split = path.split(QDir::separator(),
                                        Qt::SkipEmptyParts);
    QString root_str = path_split[0];
    HKEY    root;
    if( root_str=="HKLM" )
    {
        root = HKEY_LOCAL_MACHINE;
    }
    else if( root_str=="HKCR" )
    {
        root = HKEY_CLASSES_ROOT;
    }
    if( root_str=="HKCU" )
    {
        root = HKEY_CURRENT_USER;
    }

    // remove root from path
    path_split.removeFirst();
    path = path_split.join(QDir::separator());

    HKEY h_key;
    long reg_exist = RegOpenKeyEx(root,
            (LPCTSTR)(path.toStdString().c_str()),
            0, KEY_READ, &h_key);
    if( reg_exist!=ERROR_SUCCESS )
    {
        return false;
    }
    return true;
}

#endif
