#include "includes.h"

#define MAIN_SERVER_PORT 6872
#define BUFFER_SIZE 1024

class Socket {

    sockaddr_in serverInfo{};
    std::vector<std::string> serverPorts;

public:

    int clientSocket;
	int SERVER_PORT = MAIN_SERVER_PORT;
	bool isConnected = false;	

	~Socket() { close(clientSocket); }

	void SetupSocket(int port);
	void ConnectToMainServer();
	void ConnectToTheServer();
	std::string ListenToServer();
	void SendToServer(std::string msg);

	void GetServerList();
};