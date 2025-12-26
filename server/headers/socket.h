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
	// std::vector<int> serverSockets;
	// std::vector<sockaddr_in> serverSocketsInfo;
	// std::vector<int> serverPorts;

	struct ServerSocket {
		int socket = 0;
		int port;
		struct sockaddr_in serverInfo; 
	};

	bool isStarted = false;
	std::vector<ServerSocket> serverSockets;
	std::vector<std::unique_ptr<ServerSocket>> uServerSockets;


	// functions
	// deconstructor
	~Socket() { close(serverSocket); }

	void CreateSockets(int count);
	void SetupSocket(ServerSocket &ss);

	void HandleIncomingClients(ServerSocket &ss);
	void HandleClientConnection(std::string port, int clientSocket, std::string clientIP);

	std::string GenerateMap(int width, int height);

	void Notice(std::string msg);
	void Warning(std::string msg);
	void Error(std::string msg);
};