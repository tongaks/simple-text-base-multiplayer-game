#include "includes.h"
#include "game.h"

#define MAIN_SERVER_PORT 6872

struct ServerSocket {
	int socket = 0;
	int port;
	struct sockaddr_in serverInfo;

	int clientCount = 0;
	std::vector<int> clientsSocket;
	std::vector<std::string> clientsIP; 
	std::mutex clientMutex;

	MapInfo map;
	std::vector<Player> players;

	ServerSocket(int p) : port(p) {}
};

class Socket : public Game {

	const int MAPW = 30;
	const int MAPH = 10;

	int serverMainPort = 6872;
	int serverMainSocket = 0;

public:

	// std::string currentClientFocused;
	// std::vector<int> serverSockets;
	// std::vector<sockaddr_in> serverSocketsInfo;
	// std::vector<int> serverPorts;


	bool isStarted = false;
	// std::vector<ServerSocket> serverSockets;
	std::vector<std::unique_ptr<ServerSocket>> uServerSockets;
	std::vector<std::string> serverPortList;


	// functions
	// deconstructor
	~Socket() { 
		Warning("Closing server sockets.");
		for (const auto& ss : uServerSockets) {
			close(ss->socket); 
		}
	}

	void CreateSockets(int count);
	void SetupSocket(ServerSocket &ss);

	void HandleIncomingClients(ServerSocket &ss);
	void HandleClientConnection(ServerSocket &ss, int index);

	void Notice(std::string msg);
	void Warning(std::string msg);
	void Error(std::string msg);

	// void HandleClientConnection(ServerSocket &ss, std::string port, int clientSocket, std::string clientIP);
	// MapInfos GenerateMap(int width, int height);
	// std::vector<int> GenerateMap(int width, int height);
	// std::string GenerateMap(int width, int height);
};