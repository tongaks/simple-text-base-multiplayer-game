#include "../headers/game.h"

std::string Game::GenerateMap(int width, int height) {

	int exitX = std::rand() % (width - 2);
	int exitY = std::rand() % (height - 2);

	int posX, poxY;

	while (1) {
		// need to store players pos in playersPositions
		posX = std::rand() % (width - 2);
		posY = std::rand() % (height - 2);
		if (posX != exitX && poxY != exitY) break;
	}

	std::string playerPos = std::to_string(posX) + " " + std::to_string(poxY);
	std::string exitPos = std::to_string(exitX) + " " + std::to_string(exitY);
	return playePos + " " + exitPos;
}