#include "Common.h"

CConnection::CConnection(string host, int port)
{
    strHost = host;
    iPort = port;

    struct sockaddr_in addr;
    struct hostent *ht = gethostbyname(host.c_str());

    sock = socket (PF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr = *((struct in_addr *)ht->h_addr);

    connect(sock, (struct sockaddr *)&addr, sizeof addr);
}

CConnection::~CConnection()
{
    #if defined(SYSTEM_LINUX)
        close(sock);
    #elif defined(SYSTEM_WINDOWS)
        closesocket(sock);
    #endif
}

bool CConnection::SendData(string data)
{
    if(Connected())
    {
        send ( sock, data.c_str(), strlen(data.c_str()), 0 );
        return true;
    }

    return false;
}

bool CConnection::DataArrived(void)
{
    bool bRetVal = false;

    if(Connected())
    {
        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 0;

        fd_set readfd;
        FD_ZERO (&readfd);
        FD_SET (sock, &readfd);

        if (select (sock + 1, &readfd, NULL, NULL, &tv) != -1)
        {
            if (FD_ISSET (sock, &readfd))
            {
                bRetVal = true;
            }
        }
    }

    return bRetVal;
}

bool CConnection::Connect(string nick, string realname)
{
    strUsername = nick;
    strIdent = realname;

    if(Connected())
    {
        SendData("NICK " + nick + "\r\n");
        SendData("USER " + nick + " 0 * :" + realname + "\r\n");

        return true;
    }

    return false;
}

int CConnection::ReadData(char* buf)
{
    int iBytes = recv(sock, buf, 512, 0);
    buf[iBytes] = '\0';
    return iBytes;
}

// TODO (Callum#1#): Add support for Windows
bool CConnection::Connected(void)
{
    int error = -1;
    socklen_t len;
    #if defined(SYSTEM_LINUX)
        getsockopt(sock, SOL_SOCKET, SO_ERROR, &error, &len);
    #elif defined(SYSTEM_WINDOWS)
        getsockopt(sock, SOL_SOCKET, SO_ERROR, (char*)&error, &len);
    #endif

    return error == -1;
}

void CConnection::HandleData(string data)
{
    if(!strPacketBuffer.empty())
    {
        data = strPacketBuffer + data;
        strPacketBuffer = "";
    }

    stringstream ss(data);
    vector<string> strData;
    string tempData;

    while(getline(ss, tempData, '\n'))
    {
        strData.push_back(tempData);
    }

    vector<string>::const_iterator iter;
    for(iter = strData.begin(); iter != strData.end(); iter++)
    {
        if((*iter) == strData.back() && *(*iter).rbegin() != '\r')
        {
            strPacketBuffer = (*iter);
        }
        else
        {
            string source, command = "";
            vector<string> tokenized = Split((*iter), ' ');

            source = Split(tokenized.at(0).substr(1), '!').at(0);
            command = tokenized.at(1);

            lua_State* luaVM = g_pCore->GetLua()->GetVirtualMachine();
            lua_getglobal(luaVM, "onPacket");
            lua_pushstring(luaVM, (*iter).c_str());
            lua_pcall(luaVM, 1, 0, 0);

            if((*iter).substr(0,4) == "PING")
            {
                SendData("PO" + (*iter).substr(2) + "\r\n");

                lua_getglobal(luaVM, "onPing");
                lua_pushlightuserdata(luaVM, this);
                lua_pcall(luaVM, 1, 0, 0);
            }
            else if(command == "004")
            {
                lua_getglobal(luaVM, "onConnect");
                lua_pushlightuserdata(luaVM, this);
                lua_pcall(luaVM, 1, 0, 0);
            }
            else if(command == "PRIVMSG")
            {
                string destination, message = "";

                if(tokenized.size() >= 3)
                {
                    destination = tokenized.at(2);
                }

                if(tokenized.size() >= 4)
                {
                    for (unsigned int i = 3; i < tokenized.size(); i++)
                    {
                        message += tokenized.at(i) + " ";
                    }

                    message = message.substr(1);
                    message = message.substr(0, message.size()-1);
                }

                if(message.substr(0,1) == "")
                {
                    if(message.substr(1,7) == "VERSION")
                    {
                        SendData("NOTICE " + source + " :FoundationIRC v" + VERSION + " by Callum\r\n");
                    }
                    lua_getglobal(luaVM, destination[0] == '#' ? "onChannelCTCPMessage" : "onCTCPMessage");
                }
                else
                {
                    lua_getglobal(luaVM, destination[0] == '#' ? "onChannelMessage" : "onPrivateMessage");
                }

                lua_pushlightuserdata(luaVM, this);
                if(destination[0] == '#')
                {
                    lua_pushstring(luaVM, destination.c_str());
                }
                lua_pushstring(luaVM, message.c_str());
                lua_pushstring(luaVM, source.c_str());
                lua_pcall(luaVM, destination[0] == '#' ? 4 : 3, 0, 0);
            }
            else if(command == "NOTICE")
            {
                strServer = (*iter).substr(1, (*iter).find(" ") - 1);
            }
            else if(command == "INVITE")
            {
                string client, channel = "";
                client = tokenized.at(2);
                channel = tokenized.at(3).substr(1);

                lua_getglobal(luaVM, "onInvite");
                lua_pushlightuserdata(luaVM, this);
                lua_pushstring(luaVM, source.c_str());
                lua_pushstring(luaVM, client.c_str());
                lua_pushstring(luaVM, channel.c_str());
                lua_pcall(luaVM, 4, 0, 0);
            }
            else if(command == "JOIN")
            {
                string channel = tokenized.at(2).substr(1);

                lua_getglobal(luaVM, "onJoin");
                lua_pushlightuserdata(luaVM, this);
                lua_pushstring(luaVM, source.c_str());
                lua_pushstring(luaVM, channel.c_str());
            }
            else if(command == "QUIT")
            {
                string reason = "";

                for (unsigned int i = 2; i < tokenized.size(); i++)
                {
                    reason += tokenized.at(i) + " ";
                }

                reason = reason.substr(1);
                reason = reason.substr(0, reason.size()-1);

                lua_getglobal(luaVM, "onQuit");
                lua_pushlightuserdata(luaVM, this);
                lua_pushstring(luaVM, source.c_str());
                lua_pushstring(luaVM, reason.c_str());
            }
            else if(command == "KICK")
            {
                string channel = tokenized.at(2);
                string client = tokenized.at(3);
                string reason = "";

                for (unsigned int i = 4; i < tokenized.size(); i++)
                {
                    reason += tokenized.at(i) + " ";
                }

                reason = reason.substr(1);
                reason = reason.substr(0, reason.size()-1);

                lua_getglobal(luaVM, "onKick");
                lua_pushlightuserdata(luaVM, this);
                lua_pushstring(luaVM, channel.c_str());
                lua_pushstring(luaVM, source.c_str());
                lua_pushstring(luaVM, client.c_str());
                lua_pushstring(luaVM, reason.c_str());
            }
            else if(command == "NICK")
            {
                string newNick = tokenized.at(2);

                lua_getglobal(luaVM, "onNickChange");
                lua_pushlightuserdata(luaVM, this);
                lua_pushstring(luaVM, source.c_str());
                lua_pushstring(luaVM, newNick.c_str());
            }
            else if(command == "MODE")
            {
                string mode = tokenized.at(2);
                string channel = tokenized.at(3);

                lua_getglobal(luaVM, "onMode");
                lua_pushlightuserdata(luaVM, this);
                lua_pushstring(luaVM, channel.c_str());
                lua_pushstring(luaVM, mode.c_str());

                for (unsigned int i = 4; i < tokenized.size(); i++)
                {
                    lua_pushstring(luaVM, tokenized.at(i).c_str());
                }
            }
        }
    }
}

std::vector<std::string> CConnection::Split(const std::string &s, char delim)
{
    std::stringstream ss(s);
    std::vector<std::string> elems;
    std::string item;

    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}