#include "../headers/socket.h"

int main(int argc, char const *argv[]) {
	Socket socket1;
	// socket1.SetupSocket();
	
	while (1) {
		int choice;

		std::cout << "\n\n1. Start the server\n" << "2. Exit\n"; 

		std::cout << "> ";
		std::cin >> choice;

		if (choice == 1) {
			if (!socket1.isStarted) socket1.SetupSocket();
			else {
				std::cout << "[!] Server is already running.\n";
				continue;
			} 

		} else if (choice == 2) break;
	};

	return 0;
}