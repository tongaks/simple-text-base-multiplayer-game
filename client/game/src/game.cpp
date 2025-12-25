#include <iostream>
#include <vector>
#include <ncurses.h>


void PrintMap(int width, int height, int playerX, int playerY) {
    erase();

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

int PrintMovementSelection(int posX, int posY) {
	std::cout << "1. Move right\t2. Move left\t3. Move up\t4. Move down\n";
	printf("(%i, %i)> ", posX, posY);

	int choice = 0;
	std::cin >> choice;
	return choice;
}

bool HandleBorder(int width, int height, int posX, int posY, int plane, int dir) {
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

int main(int argc, char const *argv[]) {
	// std::vector<std::vector<int>> map;
	initscr();

	int width = 30; 
	int height = 10;
	int playerX = 2;
	int playerY = 2;

	PrintMap(width, height, playerX, playerY);
	refresh();

	int ch;
	while((ch = getch()) != 'q') { 

	    switch (ch) {
	        case 'w': case 'W': case KEY_UP:
	            if (HandleBorder(width, height, playerX, playerY, 2, 1)) {
	                playerY -= 1;
	            } break;

	        case 's': case 'S': case KEY_DOWN:
	            if (HandleBorder(width, height, playerX, playerY, 2, 2)) {
	                playerY += 1;
	            } break;

	        case 'a': case 'A': case KEY_LEFT:
	            if (HandleBorder(width, height, playerX, playerY, 1, 1)) {
	                playerX -= 1;
	            } break;

	        case 'd': case 'D': case KEY_RIGHT:
	            if (HandleBorder(width, height, playerX, playerY, 1, 2)) {
	                playerX += 1;
	            } break;

	        default:
	            break;
	    }

		// system("clear");
	    PrintMap(width, height, playerX, playerY);
	    refresh();
	}

	return 0;
}