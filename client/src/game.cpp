#include "../headers/game.h"

void Game::PrintMainMenu() {
	std::cout << "1. Start the game\n" << "2. Exit\n";
	std::cout << "> ";

	int choice = 0;
	std::cin >> choice;

	if (choice == 1) {
		StartGame();
	} else if (choice == 2) {
		exit(1);
	}
}

void Game::StartGame() {
	PrintDialoge();

	while (true) {
		
	}
}
