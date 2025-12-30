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

class Game {
public:
	std::vector<Player> playersPositions;

	std::string GenerateMap(int width, int height);
	// std::string GenerateMap(int width, int height std::string playerName);
};