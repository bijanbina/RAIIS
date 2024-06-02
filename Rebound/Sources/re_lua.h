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
    static void init();

private:
    static void registerBenjFox();
    static QString exec(const char *path);

#ifdef WIN32
    static void addRegisteryKeys();
    static int regExist(QString path);
#else
    static void patchJson();
#endif
};

#endif // RE_LUA_H
