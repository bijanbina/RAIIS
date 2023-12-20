#ifndef RE_LUA_H
#define RE_LUA_H

#include <QString>
extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}
#include "re_config.h"

class ReLua
{
public:
    ReLua();
    ~ReLua();

    QStringList getWSList();

private:
#ifdef WIN32
    void addRegisteryKeys();
    QString exec(const char *path);
    int regExist(QString path);
#endif

    lua_State *lst;
};

#endif // RE_LUA_H
