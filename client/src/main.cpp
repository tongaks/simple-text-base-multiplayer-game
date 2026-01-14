// #include "../headers/client.h"
// #include "../headers/character.h"
#include "../headers/game.h"

int main() {

	std::string name;
	std::cout << "Enter your name: ";
	std::getline(std::cin, name);


	initscr();
	Game game1;
	game1.playerName = name;

	// connect to main port
	game1.SetupSocket(game1.mainClientSocket, game1.serverMainInfo, MAIN_SERVER_PORT);
	if (!game1.isConnectedToMain) game1.ConnectToMainServer();
	game1.GetServerList();

	game1.SetupSocket(game1.clientSocket, game1.serverInfo, game1.selectedServerPort);
	game1.ConnectToTheServer();
	if (game1.CreateServerSideInstance(game1.playerName)) 
		game1.Start();

	return 0;
}