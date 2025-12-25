#include "../headers/game.h"

bool Game::CreateServerSideInstance(std::string name) {

	if (this->isConnected) {
		SendToServer("username:" + name);

		printw("[+] Instance requested. Waiting for confirmation.");
		refresh();

		int attempts = 0;
		while (attempts < 10) {

			std::string msg = ListenToServer();
			if (msg == "ok") break;

	        attempts++;
	        std::this_thread::sleep_for(std::chrono::seconds(3));
		} return true;

	} else {
		printw("[!] Not connected to the server.");
		refresh();

		return false;
	}
}

void Game::PrintMap(int width, int height, int playerX, int playerY) {
    refresh();
    erase();
    refresh();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (y == 0 || y == height - 1 || x == 0 || x == width - 1) {
                mvaddch(y, x, '#');
            } 

            else if (x == playerX + 1 && y == playerY + 1) {
                mvaddch(y, x, 'P');
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

void Game::Start() {
	int width = 30; 
	int height = 10;
	int playerX = 2;
	int playerY = 2;

	PrintMap(width, height, playerX, playerY);
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

	        default:
	            break;
	    }

	    if (allowed) {
		    std::string data = this->player_name + ":" + std::to_string(playerX) + "," + std::to_string(playerY);
		    SendToServer(data);
	    }

	    PrintMap(width, height, playerX, playerY);
	    refresh();
	}
}