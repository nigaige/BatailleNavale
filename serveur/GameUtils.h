#pragma once
#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>

using namespace std;
using namespace std;
#include <vector>
#include <iostream>
#include <string>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS


// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")


enum StateEnum;

class Server;
class ServerCallBack;

//include states
class State;
class WaitPlayerState;
class StartGameState;
class GameState;
class EndGameState;


//include game managers
class StateMachine;
class GameManager;
class GameManagerCallback;

//==============================//




#include "Server.h"
#include "ServerCallBack.h"

//include states
#include "State.h"
#include "WaitPlayerState.h"
#include "StartGameState.h"
#include "GameState.h"
#include "EndGameState.h"



//include game managers
#include "StateMachine.h"
#include "GameManager.h"
#include "GameManagerCallback.h"


