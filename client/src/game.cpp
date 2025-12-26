#include "../headers/game.h"

bool Game::CreateServerSideInstance(std::string name) {

	if (this->isConnected) {
		SendToServer("username:" + name);

		printw("[+] Instance requested. Waiting for confirmation.\n");
		refresh();

		int attempts = 0;
		while (attempts < 10) {

			std::string msg = ListenToServer();
			if (msg.find("map")) {
				printw("%s\n", msg.c_str());
				refresh();

				rawMapData = msg;
				break;
			}

	        attempts++;
	        std::this_thread::sleep_for(std::chrono::seconds(3));
		} 

		erase();
		return true;

	} else {
		printw("[!] Not connected to the server.");
		refresh();

		return false;
	}
}

Game::MapInfo Game::ParseMap(std::string mapInfo) {
	std::stringstream ss(mapInfo);
	std::string buffer;

	MapInfo processedMap;

	int count = 0;
	while (ss >> buffer) {
		printw("%s\n", buffer.c_str());
		refresh();

		if (count == 0) processedMap.playerPosX = std::stoi(buffer);
		if (count == 1) processedMap.playerPosY = std::stoi(buffer);
		if (count == 2) processedMap.exitPosX = std::stoi(buffer);
		if (count == 3) processedMap.exitPosY = std::stoi(buffer);

		// getch();
		count++;
	}

	return processedMap;
}

void Game::PrintMap(int width, int height, MapInfo map) {
    refresh();
    erase();
    refresh();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            if (y == 0 || y == height - 1 || x == 0 || x == width - 1) {
                mvaddch(y, x, '#');
            } else if (x == map.playerPosX + 1 && y == map.playerPosY + 1) {
                mvaddch(y, x, 'P');
            } else if (x == map.exitPosX + 1 && y == map.exitPosY + 1) {
                mvaddch(y, x, 'E');
            }

        }
    }

    printw("\n\n[x: %i] [y: %i]", playerX, playerY);
    refresh();
}

bool Game::HandleBorder(int width, int height, int posX, int posY, int plane, int dir) {
	// plane = 1 -> x plane
	// plane = 2 -> x plane

	// dir = 1 -> move left/down
	// dir = 2 -> move right/up


	// handle x plane
	if (plane == 1) {
		if (dir == 1) {
			if (posX - 1 <= -1) return false; // handle left
		} else if (dir == 2) {
			// 2 is the border wall
			if (posX + 1 >= width-2) return false; // handle right
		}
	} else if (plane == 2) { // handle y
		if (dir == 1) {
			if (posY - 1 <= -1) return false; // handle up
		} else if (dir == 2) {
			// 3 = 2 walls (top bottom) + the 'P'
			if (posY + 1 > height-3) return false; // handle down
		}
	}

	return true; // allow movement
}

// void Game::GetServerList() {
// 	// request server list (sockets?)
// 	SendToServer("servers");

// 	std::vector<std::string> serverList;
// 	while (1) {
// 		std::string reply = ListenToServer();
// 		if (reply.find("sockets")) {
// 			std::string buffer 
// 			std::stringstream ss(reply);

// 			while (ss >> buffer) {
// 				serverList.push_back(buffer);
// 			} break;
// 		}
// 	}

// 	int currentSelected = 0;

//     erase();
//     printw("========== Server list ==========\n\n");

//     // loop through server list
//     int count = 0;
//     for (std::string server : serverList) {
//     	printw("%i. %s\n", count+1, server);
//     	refresh();
//     	count++;
//     }

//     printw("========== Server list ==========");
//     refresh();
// }

void Game::Start() {
	int width = 30; 
	int height = 10;

	bool exitFound = false;

	MapInfo mapInfo = ParseMap(rawMapData);
	int& playerX = mapInfo.playerPosX;
	int& playerY = mapInfo.playerPosY;
	int& exitX = mapInfo.exitPosX;
	int& exitY = mapInfo.exitPosY;

	PrintMap(width, height, mapInfo);
	refresh();

	int ch;
	while((ch = getch()) != 'q') { 
		bool allowed = false;

	    switch (ch) {
	        case 'w': case 'W': case KEY_UP:
	            if (HandleBorder(width, height, playerX, playerY, 2, 1)) {
	                playerY -= 1;
	                allowed = true;
	            } break;

	        case 's': case 'S': case KEY_DOWN:
	            if (HandleBorder(width, height, playerX, playerY, 2, 2)) {
	                playerY += 1;
	                allowed = true;
	            } break;

	        case 'a': case 'A': case KEY_LEFT:
	            if (HandleBorder(width, height, playerX, playerY, 1, 1)) {
	                playerX -= 1;
	                allowed = true;
	            } break;

	        case 'd': case 'D': case KEY_RIGHT:
	            if (HandleBorder(width, height, playerX, playerY, 1, 2)) {
	                playerX += 1;
	                allowed = true;
	            } break;
	
	        case 'e': case 'E': // player pressed e in the exit
	        	if (playerX == exitX && playerY == exitY) {
	        		SendToServer("Player: " + this->player_name + " win");
	        		exitFound = true;
	        	} break;

	        default:
	            break;
	    }

	    if (allowed) {
		    std::string data = this->player_name + ":" + std::to_string(playerX) + "," + std::to_string(playerY);
		    SendToServer(data);
	    } else if (exitFound) {
	    	erase();
	    	printw("You found the exit.");
		    refresh();
		    exit(1);
	    }

	    PrintMap(width, height, mapInfo);
	    refresh();
	}
}