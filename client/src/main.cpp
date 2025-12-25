// #include "../headers/client.h"
// #include "../headers/character.h"
#include "../headers/game.h"

int main() {

	Game game1;
	game1.SetupSocket();

	std::string name;
	std::cout << "Enter your name: ";
	std::getline(std::cin, name);


	initscr();

	// Character player(name, 100, 10);

	if (!game1.isConnected) game1.ConnectToTheServer();
	game1.SetCharacterInfo(name, 100, 10);

	if (game1.CreateServerSideInstance(name)) {
		std::cout << "[+] Instance created. Continueing.\n";
		game1.Start();
	} else std::cerr << "[!] Failed to create instance. Exiting.\n";

	return 0;
}