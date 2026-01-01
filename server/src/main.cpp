#include "../headers/socket.h"

int main() {
	
	Socket socket1;	
	ServerSocket mainServerSocket(MAIN_SERVER_PORT);
	socket1.SetupSocket(mainServerSocket);
	socket1.CreateSockets(5);

	while(1) {}

	// bool stillChoice = true;
	// while (1) {

	// 	if (!stillChoice) continue;
	// 	int choice;
	// 	std::cout << "\n\n1. Start the server\n" << "2. Exit\n"; 
	// 	std::cout << "> ";
	// 	std::cin >> choice;


	// 	if (choice == 1) {
	// 		if (!socket1.isStarted) {
	// 			socket1.CreateSockets(5);
	// 			stillChoice = false;
	// 		} else {
	// 			std::cout << "[!] Server is already running.\n";
	// 			continue;
	// 		}

	// 	} else if (choice == 2) break;
	// };

	return 0;
}