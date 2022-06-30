#ifndef CCONNECTION_H
#define CCONNECTION_H

class CConnection
{
protected:
    string strHost, strUsername, strIdent, strServer, strMOTD;
    int iPort;

    unsigned int sock;
    struct sockaddr_in addrLocal;

    string strPacketBuffer;

public:
    CConnection(string host, int port);
    ~CConnection();

    bool SendData (string data);
    int ReadData(char* buf);
    void HandleData(string data);
    bool DataArrived (void);
    bool Connect(string nick, string realname);
    bool Connected(void);

    string GetHost(void) { return strHost; };
    string GetUsername(void) { return strUsername; };
    string GetIdent(void) { return strIdent; };
    string GetServer(void) { return strServer; };
    int GetPort(void) { return iPort; };
    std::vector<std::string> Split(const std::string &s, char delim);
    void AddClient(string nick);
    int GetNewClientID(void);
};

#endif