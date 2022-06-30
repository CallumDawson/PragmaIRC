#ifndef CCLIENT_H
#define CCLIENT_H

class CClient
{
private:
    string strNick, strIdent, strHost, strServer;

public:
    CClient(string nick) { strNick = nick; };
    string GetNick(void) { return strNick; };
    string GetIdent(void) { return strIdent; };
    string GetHost(void) { return strHost; };
    string GetServer(void) { return strServer; };

    void SetNick(string nick) { strNick = nick; };
    void SetIdent(string ident) { strIdent = ident; };
    void SetHost(string host) { strHost = host; };
    void SetServer(string server) { strServer = server; };
};

#endif