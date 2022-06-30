# PragmaIRC
An IRC framework that I created in C++ somewhere between 2011-2015. It incorporates Lua 5.2, and allows the user to provide their own logic using a "script.lua" file. A single instance of the bot can use the same script file to run an unlimited number of IRC connections, making it extremely flexible. The custom Lua VM functions and events, along with an example script, are below.

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

## Example Script
```lua
local gtanet = createConnection("irc.gtanet.com",6667)
connect(gtanet,"TestBot","Test Bot")

function onConnect(connection)
	if connection == gtanet then
		joinChannel(connection,"#gti")
	end
end

function onPrivateMessage(connection,message,client)
	sendMessage(connection,client,"I am a robot! Type !info for more information.")
end

function onChannelMessage(connection,channel,message,client)
	if message:lower():sub(1,7) == "!8ball " then
		local responses = {"It is certain","Without a doubt","Yes, definately","You may rely on it","As I see it, yes","Most likely","Yes","Signs point to yes","Ask again later","That's a secret","Don't count on it","No","Sources say no","Very doubtful"}
		sendMessage(connection,channel,client..": "..responses[math.random(#responses)])
	end
end

function onPacket(data)
	output(data)
end

function onMOTDFinish(motd)
	output(motd)
end

function onChannelCTCPMessage(connection,channel,ctcp,source)
	output("Received CTCP \'"..ctcp.."\' from "..source.." on "..channel)
end

function onCTCPMessage(connection,ctcp,source)
	output("Received CTCP \'"..ctcp.."\' from "..source)
end
```
