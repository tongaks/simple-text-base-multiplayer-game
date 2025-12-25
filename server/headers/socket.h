#include "includes.h"

class Socket {

	const int MAPW = 30;
	const int MAPH = 10;

	// server
	int serverSocket = 0;
	int serverPort = 3423;
	struct sockaddr_in serverInfo;

	// client related
	int clientConnectedCount = 0;
	std::vector<int> clientsSocket;
	std::vector<std::string> clientsConnected;
	std::string currentClientFocused;
	std::mutex clientMutexHandler;

public:
	bool isStarted = false;

	// deconstructor
	~Socket() { close(serverSocket); }

	void SetupSocket();

	void HandleIncomingClients();
	void HandleClientConnection(int clientSocket, std::string clientIP);

	std::string GenerateMap(int width, int height);

	void Notice(std::string msg);
	void Warning(std::string msg);
	void Error(std::string msg);
};