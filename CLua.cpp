#include "Common.h"

CLua::CLua()
{
    m_Lua = luaL_newstate();
    luaL_openlibs(m_Lua);

    RegisterFunctions();

    if ( luaL_loadfile(m_Lua, "script.lua") != LUA_ERRFILE && lua_pcall(m_Lua, 0, 0, 0) == 0)
	{
        return;
	}
    printf("ERROR: Could not load Lua script!\n");
}

CLua::~CLua(void)
{
    lua_close(m_Lua);
}

void CLua::RegisterFunctions(void)
{
    lua_register (m_Lua, "output", CLuaFunctions::Output);
    lua_register (m_Lua, "createConnection", CLuaFunctions::CreateConnection);
    lua_register (m_Lua, "connect", CLuaFunctions::Connect);
    lua_register (m_Lua, "joinChannel", CLuaFunctions::JoinChannel);
    lua_register (m_Lua, "partChannel", CLuaFunctions::PartChannel);
    lua_register (m_Lua, "getConnectionHost", CLuaFunctions::GetConnectionHost);
    lua_register (m_Lua, "getConnectionPort", CLuaFunctions::GetConnectionPort);
    lua_register (m_Lua, "getConnectionServer", CLuaFunctions::GetConnectionServer);
    lua_register (m_Lua, "getConnectionUsername", CLuaFunctions::GetConnectionUsername);
    lua_register (m_Lua, "getConnectionIdent", CLuaFunctions::GetConnectionIdent);
    lua_register (m_Lua, "sendMessage", CLuaFunctions::SendMessage);
    lua_register (m_Lua, "sendRaw", CLuaFunctions::SendRaw);
    lua_register (m_Lua, "kickClient", CLuaFunctions::KickClient);
    lua_register (m_Lua, "getVersion", CLuaFunctions::GetVersion);
    lua_register (m_Lua, "getTickCount", CLuaFunctions::GetTickCount_);
    lua_register (m_Lua, "oper", CLuaFunctions::Oper);
    lua_register (m_Lua, "die", CLuaFunctions::Die);
    lua_register (m_Lua, "restart", CLuaFunctions::Restart);
}