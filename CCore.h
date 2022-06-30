#ifndef CCORE_H
#define CCORE_H

class CCore
{
public:
    CConnectionManager* GetConnectionManager    (void)                                      { return m_ConnectionManager; };
    CLua*               GetLua                  (void)                                      { return m_Lua; };

    void                SetConnectionManager    (CConnectionManager* connectionManager)     { m_ConnectionManager = connectionManager; };
    void                SetLua                  (CLua* lua)                                 { m_Lua = lua; };

private:
    CLua*               m_Lua;
    CConnectionManager* m_ConnectionManager;
};

#endif