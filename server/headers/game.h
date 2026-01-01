#include "includes.h"

struct Player {
	std::string playerName;
	int posX;
	int posY;

	Player(std::string pName, int pX, int pY) {
		this->playerName = pName;
		this->posX = pX;
		this->posY = pY;
	}
};

struct MapInfo {
	int mapW, mapH, exitX, exitY;
	MapInfo(int w, int h, int eX, int eY) {
		this->mapW = w;
		this->mapH = h;
		this->exitX = eX;
		this->exitY = eY;
	}
};



class Game {
public:
	std::vector<Player> playersPositions;

	MapInfo GenerateMap(int width, int height);
	Player CreatePlayer(std::string pName, MapInfo mInfo);

	// old
	// int GenerateMap(int width, int height);
	// std::string GenerateMap(int width, int height);
	// Player CreatePlayer(std::string pName, int exitX, int exitY);
	// std::string GenerateMap(int width, int height std::string playerName);
};