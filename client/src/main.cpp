#include "../headers/client.h"

int main(int argc, char const *argv[]) {
	Socket sock1;
	sock1.SetupSocket();

	std::string name;
	std::cout << "Enter your name: ";
	std::getline(std::cin, name);

	// sock1.SendToServer(name);

	while (1) {
		if (!sock1.isConnected) sock1.ConnectToTheServer();
		sock1.ListenToServer();
	}

	return 0;
}