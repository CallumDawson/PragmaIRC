#include "Common.h"

void CConnectionManager::DoPulse(void)
{
	ConnectionIterator conIterator;
	for (conIterator = connMap.begin (); conIterator != connMap.end (); ++conIterator)
	{
		CConnection* connection = conIterator->second;
		if ( connection->DataArrived() )
		{
            char szBuffer[512];
			connection->ReadData(&szBuffer[0]);
			connection->HandleData(string(&szBuffer[0]));
		}
	}
}

CConnection* CConnectionManager::CreateConnection(string host, int port)
{
	int iID = GetNewConnectionID();

	if ( iID >= 0 )
	{
		CConnection* connection = new CConnection(host, port);
		connMap[iID] = connection;

		return connection;
	}

	return NULL;
}

int CConnectionManager::GetNewConnectionID ( void )
{
	int nRetVal = 0;

	ConnectionIterator conIterator;
	for (conIterator = connMap.begin (); conIterator != connMap.end (); ++conIterator, nRetVal++)
	{
		if (nRetVal != conIterator->first)
		{
			break;
		}
	}

	return nRetVal;
}