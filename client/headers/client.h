#include "includes.h"

#define MAIN_SERVER_PORT 6872
#define BUFFER_SIZE 1024

// struct MapInfo {
// 	std::vector<Players> currentPlayers;
// 	int exitX, exitY;
// 	int mapW, mapH;
// };

class Socket {
public:

    sockaddr_in serverMainInfo{};
    sockaddr_in serverInfo{};

	bool isConnectedToMain = false;
	bool isConnected = false;

    std::vector<std::string> serverPorts;
	int SERVER_PORT;

    int clientSocket;
    int mainClientSocket;


    // void ListenForNewPlayers(int& cSocket, MapInfo& map);

	~Socket() { close(clientSocket); }
	void SetupSocket(int& cSocket, sockaddr_in &server, int port);
	void GetServerList();

	void ConnectToMainServer();
	void ConnectToTheServer();

	std::string ListenToServer(int& cSocket);
	void SendToServer(int& cSocket, std::string msg);
};