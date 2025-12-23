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

int PrintMovementSelection() {
	std::cout << "1. Move right\t2. Move left\t3. Move up\t4. Move down\n";
	std::cout << "> ";

	int choice = 0;
	std::cin >> choice;
	return choice;
}

int main(int argc, char const *argv[]) {
	// std::vector<std::vector<int>> map;

	int width = 30; 
	int height = 10;
	int playerX = 2;
	int playerY = 2;

	PrintMap(30, 10, 2, 2);

	while (1) {
		switch (PrintMovementSelection()) {
		case 1:
			playerX += 1;
			break;
		case 2:
			playerX -= 1;
			break;
		case 3:
			playerY += 1;
			break;
		case 4:
			playerY -= 1;
			break;
		default:
			break;
		}

		PrintMap(width, height, playerX, playerY);
	}

	return 0;
}