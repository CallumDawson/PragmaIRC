#include "Common.h"

int CLuaFunctions::Output(lua_State* luaVM)
{
    if(lua_isstring(luaVM, 1))
    {
        printf("%s\n", lua_tostring(luaVM, 1));

        lua_pushboolean(luaVM, true);
        return 1;
    }

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaFunctions::CreateConnection(lua_State* luaVM)
{
    if(lua_isstring(luaVM, 1))
    {
        if(lua_isnumber(luaVM, 2))
        {
            CConnection* connection = g_pCore->GetConnectionManager()->CreateConnection(lua_tostring(luaVM, 1), lua_tonumber(luaVM, 2));

            lua_pushlightuserdata(luaVM, connection);
            return 1;
        }
    }

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaFunctions::Connect(lua_State* luaVM)
{
    if(lua_islightuserdata(luaVM, 1))
    {
        if(lua_isstring(luaVM, 2))
        {
            if(lua_isstring(luaVM, 3))
            {
                CConnection* connection = (CConnection*)lua_touserdata(luaVM, 1);
                bool bConnected = connection->Connect(lua_tostring(luaVM, 2), lua_tostring(luaVM, 3));

                lua_pushboolean(luaVM, bConnected);
                return 1;
            }
        }
    }

    lua_pushboolean (luaVM, false);
    return 1;
}

int CLuaFunctions::JoinChannel(lua_State* luaVM)
{
    if(lua_islightuserdata(luaVM, 1))
    {
        if(lua_isstring(luaVM, 2))
        {
            string channel = lua_tostring(luaVM, 2);

            CConnection* connection = (CConnection*)lua_touserdata(luaVM, 1);
            bool bJoined = connection->SendData("JOIN " + channel + "\r\n");

            lua_pushboolean(luaVM, bJoined);
            return 1;
        }
    }

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaFunctions::PartChannel(lua_State* luaVM)
{
    if(lua_islightuserdata(luaVM, 1))
    {
        if(lua_isstring(luaVM, 2))
        {
            if(lua_isstring(luaVM, 3))
            {
                string channel = lua_tostring(luaVM, 2);
                string reason = lua_tostring(luaVM, 3);

                CConnection* connection = (CConnection*)lua_touserdata(luaVM, 1);
                bool bParted = connection->SendData("PART " + channel + " :" + reason + "\r\n");

                lua_pushboolean(luaVM, bParted);
                return 1;
            }
        }
    }

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaFunctions::GetConnectionHost(lua_State* luaVM)
{
    if(lua_islightuserdata(luaVM, 1))
    {
        CConnection* connection = (CConnection*)lua_touserdata(luaVM, 1);

        lua_pushstring(luaVM, connection->GetHost().c_str());
        return 1;
    }

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaFunctions::GetConnectionPort(lua_State* luaVM)
{
    if(lua_islightuserdata(luaVM, 1))
    {
        CConnection* connection = (CConnection*)lua_touserdata(luaVM, 1);

        lua_pushnumber(luaVM, connection->GetPort());
        return 1;
    }

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaFunctions::GetConnectionServer(lua_State* luaVM)
{
    if(lua_islightuserdata(luaVM, 1))
    {
        CConnection* connection = (CConnection*)lua_touserdata(luaVM, 1);

        lua_pushstring(luaVM, connection->GetServer().c_str());
        return 1;
    }

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaFunctions::GetConnectionUsername(lua_State* luaVM)
{
    if(lua_islightuserdata(luaVM, 1))
    {
        CConnection* connection = (CConnection*)lua_touserdata(luaVM, 1);

        lua_pushstring(luaVM, connection->GetUsername().c_str());
        return 1;
    }

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaFunctions::GetConnectionIdent(lua_State* luaVM)
{
    if(lua_islightuserdata(luaVM, 1))
    {
        CConnection* connection = (CConnection*)lua_touserdata(luaVM, 1);

        lua_pushstring(luaVM, connection->GetIdent().c_str());
        return 1;
    }

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaFunctions::SendMessage(lua_State* luaVM)
{
    if(lua_islightuserdata(luaVM, 1))
    {
        if(lua_isstring(luaVM, 2))
        {
            if(lua_isstring(luaVM, 3))
            {
                CConnection* connection = (CConnection*)lua_touserdata(luaVM, 1);
                string destination = lua_tostring(luaVM, 2);
                string message = lua_tostring(luaVM, 3);

                bool bSent = connection->SendData("PRIVMSG " + destination + " " + message + "\r\n");

                lua_pushboolean(luaVM, bSent);
                return 1;
            }
        }
    }

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaFunctions::SendRaw(lua_State* luaVM)
{
    if(lua_islightuserdata(luaVM, 1))
    {
        if(lua_isstring(luaVM, 2))
        {
            CConnection* connection = (CConnection*)lua_touserdata(luaVM, 1);
            string raw = lua_tostring(luaVM, 2);

            bool bSent = connection->SendData(raw + "\r\n");

            lua_pushboolean(luaVM, bSent);
            return 1;
        }
    }

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaFunctions::KickClient(lua_State* luaVM)
{
    if(lua_islightuserdata(luaVM, 1))
    {
        if(lua_isstring(luaVM, 2))
        {
            if(lua_isstring(luaVM, 3))
            {
                CConnection* connection = (CConnection*)lua_touserdata(luaVM, 1);
                string channel = lua_tostring(luaVM, 2);
                string client = lua_tostring(luaVM, 3);
                string reason = connection->GetUsername();

                if(lua_isstring(luaVM, 4))
                {
                    reason = lua_tostring(luaVM, 4);
                }

                bool bSent = connection->SendData("KICK " + channel + " " + client + " :" + reason + "\r\n");

                lua_pushboolean(luaVM, bSent);
                return 1;
            }
        }
    }

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaFunctions::GetVersion(lua_State* luaVM)
{
    lua_pushstring(luaVM, VERSION);
    return 1;
}

int CLuaFunctions::GetTickCount_(lua_State* luaVM)
{
    #if defined(SYSTEM_LINUX)
        struct timespec now;
        if(!clock_gettime(CLOCK_MONOTONIC, &now))
        {
            double dTick = now.tv_sec*1000+now.tv_nsec/1000000;
            lua_pushnumber(luaVM, dTick);
            return 1;
        }
    #elif defined(SYSTEM_WINDOWS)
        lua_pushnumber(luaVM, GetTickCount());
        return 1;
    #endif
    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaFunctions::Oper(lua_State* luaVM)
{
    if(lua_islightuserdata(luaVM, 1))
    {
        if(lua_isstring(luaVM, 2))
        {
            if(lua_isstring(luaVM, 3))
            {
                CConnection* connection = (CConnection*)lua_touserdata(luaVM, 1);
                string username = lua_tostring(luaVM, 2);
                string password = lua_tostring(luaVM, 3);

                bool bSent = connection->SendData("OPER " + username + " " + password + "\r\n");

                lua_pushboolean(luaVM, bSent);
                return 1;
            }
        }
    }

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaFunctions::Die(lua_State* luaVM)
{
    if(lua_islightuserdata(luaVM, 1))
    {
        CConnection* connection = (CConnection*)lua_touserdata(luaVM, 1);

        bool bSent = connection->SendData("DIE\r\n");

        lua_pushboolean(luaVM, bSent);
        return 1;
    }

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaFunctions::Restart(lua_State* luaVM)
{
    if(lua_islightuserdata(luaVM, 1))
    {
        CConnection* connection = (CConnection*)lua_touserdata(luaVM, 1);

        bool bSent = connection->SendData("RESTART\r\n");

        lua_pushboolean(luaVM, bSent);
        return 1;
    }

    lua_pushboolean(luaVM, false);
    return 1;
}