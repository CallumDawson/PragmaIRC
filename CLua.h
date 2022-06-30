#ifndef CLUA_H
#define CLUA_H

#include "lua.hpp"

class CLua
{
public:
    CLua ();
    ~CLua (void);

    lua_State* GetVirtualMachine(void) { return m_Lua; };

private:
    lua_State* m_Lua;

    void RegisterFunctions (void);
};

#endif