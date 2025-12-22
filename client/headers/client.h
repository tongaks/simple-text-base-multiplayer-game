#include "includes.h"

#define SERVER_PORT 3423
#define BUFFER_SIZE 1024

class Socket {

    int clientSocket;
    sockaddr_in serverInfo{};


public:
	~Socket() { close(clientSocket); }

	void SetupSocket();
	void ConnectToTheServer();
	void ListenToServer();
	void SendToServer();
};