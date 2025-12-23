#include <iostream>
#include <vector>

void PrintMap(int width, int height) {
	for (int i = 0; i < width; i++) {
		std::cout << "#";
	} std::cout << '\n';


	for (int d = 0; d < height; d++) {
		for (int i = 0; i < width; i++) {
			if (i == 0) std::cout << "#";
			else if (i == width-1) std::cout << "#";
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

	PrintMap(30, 10);

	switch (PrintMovementSelection()) {
	case 1:
		std::cout << "Move to right\n";
		break;
	case 2:
		std::cout << "Move to left\n";
		break;
	case 3:
		std::cout << "Move to up\n";
		break;
	case 4:
		std::cout << "Move to down\n";
		break;
	default:
		std::cout << "Unknown movement\n";
		break;
	}

	return 0;
}