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
    void registerBenjFox();
    QString exec(const char *path);

#ifdef WIN32
    void addRegisteryKeys();
    int regExist(QString path);
#else
    void patchJson();
#endif

    lua_State *lst;
};

#endif // RE_LUA_H
