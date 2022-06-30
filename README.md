# PragmaIRC
An IRC bot I coded in C++ somewhere between 2011-2015. The bot does not come shipped with any logic, but rather it incorporates Lua 5.2 and allows the user to provide a "script.lua" file. The custom Lua VM functions and events are listed below.

## Functions
* output
* createConnection
* connect
* joinChannel
* partChannel
* getConnectionHost
* getConnectionPort
* getConnectionServer
* getConnectionUsername
* getConnectionIdent
* sendMessage
* sendRaw
* kickClient
* getVersion
* getTickCount
* oper
* die
* restart

## Events
* onPacket
* onPing
* onConnect
* onCTCPMessage
* onChannelCTCPMessage
* onPrivateMessage
* onChannelMessage
* onInvite
* onJoin
* onQuit
* onKick
* onNickChange
* onMode
