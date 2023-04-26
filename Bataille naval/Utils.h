#pragma once

#include <SFML/Graphics.hpp>

#include <crtdbg.h>
#include <winsock2.h>
#include <Windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <string.h>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define GRID_SIZE_X 10
#define GRID_SIZE_Y 10
#define WINDOWSIZE_X 200
#define WINDOWSIZE_Y 200

class Ship;
class Map;
class Player;
class GameManager;
class GameInput;
class Client;

#include "Ship.h"
#include "Map.h"
#include "GameManager.h"
#include "Player.h"
#include "GameInput.h"
#include "Client.h"
