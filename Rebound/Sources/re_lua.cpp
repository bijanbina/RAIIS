#include "re_lua.h"
#include <QtDebug>
#include <QDir>
#include "backend.h"

#define WS_SC_PATH "Scripts/Firefox/getWS.sh"

ReLua::ReLua()
{
#ifdef WIN32
    lst = luaL_newstate();
    luaL_openlibs(lst);
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
