#include "../headers/game.h"

std::string Game::GenerateMap(int width, int height) {

	// client randomize their own position
	int exitX = std::rand() % (width - 2);
	int exitY = std::rand() % (height - 2);

	std::string exitPos = std::to_string(exitX) + " " + std::to_string(exitY);
	// Notice("Map exit: " + exitPos);

	return exitPos;
}