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

#include <sstream>

namespace patch
{
    template < typename T > std::string to_string(const T& n)
    {
        std::ostringstream stm;
        stm << n;
        return stm.str();
    }
}






// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define GRID_SIZE_X 10
#define GRID_SIZE_Y 10
#define WINDOWSIZE_X 1000
#define WINDOWSIZE_Y 500

#define PLAYER_1_GRID_POSX 50
#define PLAYER_1_GRID_POSY 100
#define PLAYER_2_GRID_POSX 400
#define PLAYER_2_GRID_POSY 100
#define SLOT_SIZE_X 30
#define SLOT_SIZE_Y 30


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
