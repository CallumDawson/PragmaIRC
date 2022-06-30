# PragmaIRC
An IRC framework that I created in C++ somewhere between 2011-2015. It incorporates Lua 5.2, and allows the user to provide their own logic using a "script.lua" file. The custom Lua VM functions and events are listed below.

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
