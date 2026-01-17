#include "../headers/game.h"
#include "../headers/socket.h"

MapInfo Game::GenerateMap(int width, int height) {
	int exitX = std::rand() % (width - 2);
	int exitY = std::rand() % (height - 2);

	MapInfo mapTemp; mapTemp.Setup(width, height, exitX, exitY);
	return mapTemp;
}

// old
// Player Game::CreatePlayer(std::string pName, MapInfo mInfo) {
Player Game::CreatePlayer(std::string pName, MapInfo mInfo, ServerSocket& ss) {
	int posX, posY;
	bool allowed = false;

	// old
		// do {
		// 	posX = std::rand() % (mInfo.mapW - 2);
		// 	posY = std::rand() % (mInfo.mapH - 2);

		// 	// check if there's existing position
		// 	if (this->playersPositions.size() > 0) {
		// 		for (const auto& p : this->playersPositions) {
		// 		    if (p.posX != posX && p.posY != posY) continue;
		// 		    else break; 
		// 		}			
		// 	}

		// 	if (posX != mInfo.exitX && posY != mInfo.exitY) {
		// 		allowed = true;
		// 		break;
		// 	}

		// } while (!allowed);

	// new
	do {
		posX = std::rand() % (mInfo.mapW - 2);
		posY = std::rand() % (mInfo.mapH - 2);

		// check if there's existing position
		if (ss.clientCount > 0) {
			for (const auto& p : ss.currentPlayers) {
			    if (p.posX != posX && p.posY != posY) continue;
			    else break; 
			}			
		}

		if (posX != mInfo.exitX && posY != mInfo.exitY) {
			allowed = true; break;
		}

	} while (!allowed);


	// player ID generation
	bool idOk = false;
	int pID = std::rand() % (9999 + 1 - 4000) + 4000;
	if (ss.clientCount > 1) {
		do {
			pID = std::rand() % (9999 + 1 - 4000) + 4000;
			std::cout << "Player count: " << ss.clientCount << '\n';
			for (auto& p : ss.currentPlayers) {
				if (p.playerID == pID) continue;
				else break;
			}
		} while (!idOk);
	}

	Player playerTemp(pName, posX, posY, pID);
	return playerTemp;
}