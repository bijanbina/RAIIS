#include "re_lua.h"
#include <QtDebug>
#include <QDir>

ReLua::ReLua()
{
    lst = luaL_newstate();
    luaL_openlibs(lst);
}

void ReLua::run()
{ ///FIXME: solve directory problem
    QString current_dir = QDir::currentPath();
    QDir::setCurrent(RE_FIREFOX_DIR);

    luaL_loadfile(lst, "getWS.lua");
    lua_pcall(lst, 0, LUA_MULTRET, 0);

    lua_getglobal(lst, "url_list");
    QString output = lua_tostring(lst, -1);

    qDebug() << "LUA : " << output;
    QDir::setCurrent(current_dir);
}

ReLua::~ReLua()
{
    lua_close(lst);
}
