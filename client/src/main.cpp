// #include "../headers/client.h"
// #include "../headers/character.h"
#include "../headers/game.h"

int main() {

	// int port;
	// std::cout << "Enter server port: ";
	// std::cin >> port;

	std::string name;
	std::cout << "Enter your name: ";
	std::getline(std::cin, name);

	initscr();

	Game game1;


	game1.SetupSocket(game1.mainClientSocket, game1.serverMainInfo, MAIN_SERVER_PORT);
	if (!game1.isConnected) game1.ConnectToMainServer();
	game1.GetServerList();

	game1.SetupSocket(game1.clientSocket, game1.serverInfo, game1.selectedServerPort);
	game1.ConnectToTheServer();
	game1.Start();


	// game1.ConnectToTheServer(game1.selectedServerPort, game1.gameSocket);
	// game1.Start();


	// game1.SetCharacterInfo(name, 100, 10);
	// if (game1.CreateServerSideInstance(name)) {
	// 	std::cout << "[+] Instance created. Continueing.\n";
	// 	game1.Start();
	// } else std::cerr << "[!] Failed to create instance. Exiting.\n";

	return 0;
}