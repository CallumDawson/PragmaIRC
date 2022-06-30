#ifndef COMMON_H
#define COMMON_H

#define VERSION "1"

#ifdef _WIN32
    #define SYSTEM_WINDOWS
#elif __APPLE__
    #define SYSTEM_MACINTOSH
#elif __GNUC__
    #define SYSTEM_LINUX
#endif

#include <map>
#include <string.h>
#include <vector>
#include <sstream>
#include <Winsock2.h>
#include <ws2tcpip.h>

#include "CConnection.h"
#include "CConnectionManager.h"
#include "CLua.h"
#include "CLuaFunctions.h"
#include "CCore.h"
#include "lua.hpp"

using namespace std;

extern CCore* g_pCore;

#endif