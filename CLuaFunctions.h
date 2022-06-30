#ifndef CLUAFUNCTIONS_H
#define CLUAFUNCTIONS_H

#include "lua.hpp"

class CLuaFunctions
{
public:
    CLuaFunctions ( void );
    static int Output (lua_State* luaVM);
    static int CreateConnection (lua_State* luaVM);
    static int Connect(lua_State* luaVM);
    static int JoinChannel(lua_State* luaVM);
    static int PartChannel(lua_State* luaVM);
    static int GetConnectionHost(lua_State* luaVM);
    static int GetConnectionPort(lua_State* luaVM);
    static int GetConnectionServer(lua_State* luaVM);
    static int GetConnectionUsername(lua_State* luaVM);
    static int GetConnectionIdent(lua_State* luaVM);
    static int SendMessage(lua_State* luaVM);
    static int SendRaw(lua_State* luaVM);
    static int KickClient(lua_State* luaVM);
    static int GetVersion(lua_State* luaVM);
    static int GetTickCount_(lua_State* luaVM);
    static int Oper(lua_State* luaVM);
    static int Die(lua_State* luaVM);
    static int Restart(lua_State* luaVM);
};

#endif