#pragma once

#include <winsock2.h>

using namespace std;
#include <vector>
#include <iostream>

enum StateEnum;

//include states
class State;
class WaitPlayerState;
class StartGameState;


//include game managers
class StateMachine;
class GameManager;

//==============================//

//include states
#include "State.h"
#include "WaitPlayerState.h"
#include "StartGameState.h"



//include game managers
#include "StateMachine.h"
#include "GameManager.h"