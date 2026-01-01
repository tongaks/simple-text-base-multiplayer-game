#include "includes.h"

#define MAIN_SERVER_PORT 6872
#define BUFFER_SIZE 1024

class Socket {
public:

    sockaddr_in serverMainInfo{};
    sockaddr_in serverInfo{};
    std::vector<std::string> serverPorts;

	int SERVER_PORT;
	bool isConnected = false;	

    int clientSocket;
    int mainClientSocket;



	~Socket() { close(clientSocket); }
	void SetupSocket(int& cSocket, sockaddr_in &server, int port);
	void GetServerList();

	void ConnectToMainServer();
	void ConnectToTheServer();

	std::string ListenToServer(int& cSocket);
	void SendToServer(int& cSocket, std::string msg);
};