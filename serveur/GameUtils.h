#pragma once

#include <winsock2.h>

using namespace std;
#include <vector>
#include <iostream>

#define _CRT_SECURE_NO_WARNINGS

enum StateEnum;

class Server;

//include states
class State;
class WaitPlayerState;
class StartGameState;
class GameState;
class EndGameState;


//include game managers
class StateMachine;
class GameManager;

//==============================//

#include "Server.h"

//include states
#include "State.h"
#include "WaitPlayerState.h"
#include "StartGameState.h"
#include "GameState.h"
#include "EndGameState.h"



//include game managers
#include "StateMachine.h"
#include "GameManager.h"