#include "../headers/game.h"

MapInfo Game::GenerateMap(int width, int height) {
	int exitX = std::rand() % (width - 2);
	int exitY = std::rand() % (height - 2);

	MapInfo mapTemp; mapTemp.Setup(width, height, exitX, exitY);
	return mapTemp;
}

Player Game::CreatePlayer(std::string pName, MapInfo mInfo) {
	int posX, posY;
	bool allowed = false;

	do {
		posX = std::rand() % (mInfo.mapW - 2);
		posY = std::rand() % (mInfo.mapH - 2);

		// check if there's existing position
		if (this->playersPositions.size() > 0) {
			for (const auto& p : this->playersPositions) {
			    if (p.posX != posX && p.posY != posY) continue;
			    else break; 
			}			
		}

		if (posX != mInfo.exitX && posY != mInfo.exitY) {
			allowed = true;
			break;
		}

	} while (!allowed);


	Player playerTemp(pName, posX, posY);
	return playerTemp;
}