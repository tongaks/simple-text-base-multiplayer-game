#include <iostream>
#include <vector>

void PrintMap(int width, int height, int playerX, int playerY) {
	for (int i = 0; i < width; i++) {
		std::cout << "#";
	} std::cout << '\n';


	for (int d = 0; d < height; d++) {
		for (int i = 0; i < width; i++) {
			if (i == 0) std::cout << "#";
			else if (i == width-1) std::cout << "#";
			// print player position
			else if (i == playerX + 1 && d == playerY) std::cout << "P";
			else std::cout << " ";
		} std::cout << '\n';
	}


	for (int i = 0; i < width; i++) {
		std::cout << "#";
	} std::cout << "\n\n";
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
			if (posY + 1 >= height) return false; // handle down
		}
	}

	return true; // allow movement
}

int main(int argc, char const *argv[]) {
	// std::vector<std::vector<int>> map;

	int width = 40; 
	int height = 20;
	int playerX = 2;
	int playerY = 2;

	PrintMap(width, height, playerX, playerY);

	while (1) {
		switch (PrintMovementSelection(playerX, playerY)) {
		case 1: // right
			if (HandleBorder(width, height, playerX, playerY, 1, 2)) {
				playerX += 1;
			} break;
		case 2: // left
			if (HandleBorder(width, height, playerX, playerY, 1, 1)) {
				playerX -= 1;
			} break;
		case 3:
			if (HandleBorder(width, height, playerX, playerY, 2, 1)) {
				playerY -= 1;
			} break;
		case 4:
			if (HandleBorder(width, height, playerX, playerY, 2, 2)) {
				playerY += 1;
			} break;
		default:
			break;
		}

		PrintMap(width, height, playerX, playerY);
	}

	return 0;
}