#ifndef CCONNECTIONMANAGER_H
#define CCONNECTIONMANAGER_H

#include "Common.h"

typedef std::map<const int, CConnection*> ConnectionMap;
typedef std::map<const int, CConnection*>::const_iterator ConnectionIterator;

class CConnectionManager
{
public:
    void DoPulse(void);
    CConnection* CreateConnection(string host, int port);
    bool DeleteConnection(void);
private:
    ConnectionMap connMap;
    int GetNewConnectionID(void);
};

#endif