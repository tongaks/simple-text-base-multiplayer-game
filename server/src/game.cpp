#include "../headers/game.h"

std::string Game::GenerateMap(int width, int height) {

	int exitX = std::rand() % (width - 2);
	int exitY = std::rand() % (height - 2);

	int posX, posY;
	bool allowed = false;

	while (1) {
		// need to store players pos in playersPositions
		posX = std::rand() % (width - 2);
		posY = std::rand() % (height - 2);

		// check if there's existing position
		for (const auto& p : playersPositions) {
		    if (p.posX != posX && p.posY != posY) continue;
		    else break; 
		}

		if (posX != exitX && posY != exitY) {
			allowed = true;
			break;
		}
	}

	// generate again if there's player pos conflict
	if (!allowed) GenerateMap(width, height);


	// create player
	// Player playerTemp(playerName, posX, posY);
	// playersPositions.emplace_back(playerTemp);


	std::string playerPos = std::to_string(posX) + " " + std::to_string(posY);
	std::string exitPos = std::to_string(exitX) + " " + std::to_string(exitY);
	return playerPos + " " + exitPos;
}