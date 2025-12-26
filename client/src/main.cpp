// #include "../headers/client.h"
// #include "../headers/character.h"
#include "../headers/game.h"

int main() {

	int port;
	std::cout << "Enter server port: ";
	std::cin >> port;

	std::string name;
	std::cout << "Enter your name: ";
	std::getline(std::cin, name);

	Game game1;
	game1.SERVER_PORT = port;
	game1.SetupSocket();

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