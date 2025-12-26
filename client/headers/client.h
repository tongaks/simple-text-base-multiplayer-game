#include "includes.h"

// #define SERVER_PORT 6872
#define BUFFER_SIZE 1024

class Socket {

    int clientSocket;
    sockaddr_in serverInfo{};

public:
	~Socket() { close(clientSocket); }
	int SERVER_PORT = 0;

	bool isConnected = false;	

	void SetupSocket();
	void ConnectToTheServer();
	std::string ListenToServer();
	void SendToServer(std::string msg);

	void GetServerList();
};