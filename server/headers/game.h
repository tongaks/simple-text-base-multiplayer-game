#ifndef GAME_H
#define GAME_H

#include "includes.h"
// #include "socket.h"

struct ServerSocket;

struct Player {
	std::string playerName;
	int playerID = -1;
	int posX;
	int posY;

	Player(std::string pName, int pX, int pY, int id) {
		this->playerName = pName;
		this->posX = pX;
		this->posY = pY;
		this->playerID = id;
	}
};

struct MapInfo {
	int mapW, mapH, exitX, exitY;
	void Setup(int w, int h, int eX, int eY) {
		this->mapW = w;
		this->mapH = h;
		this->exitX = eX;
		this->exitY = eY;
	}	

	// MapInfo(int w, int h, int eX, int eY) {
	// 	this->mapW = w;
	// 	this->mapH = h;
	// 	this->exitX = eX;
	// 	this->exitY = eY;
	// }
};



class Game {
public:
	std::vector<Player> playersPositions;
	std::vector<std::vector<int>> playersPositionsTemp;
	

	MapInfo GenerateMap(int width, int height);
	// Player CreatePlayer(std::string pName, MapInfo mInfo);
	Player CreatePlayer(std::string pName, MapInfo mInfo, ServerSocket& ss);

	// old
	// Player CreatePlayer(std::string pName, MapInfo mInfo);
	// int GenerateMap(int width, int height);
	// std::string GenerateMap(int width, int height);
	// Player CreatePlayer(std::string pName, int exitX, int exitY);
	// std::string GenerateMap(int width, int height std::string playerName);
};


#endif