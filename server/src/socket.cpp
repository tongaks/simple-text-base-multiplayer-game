#include "../headers/socket.h"
#include "../headers/game.h"

void Socket::SetupSocket() {
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    serverInfo.sin_family = AF_INET;
    serverInfo.sin_port = htons(serverPort);
    serverInfo.sin_addr.s_addr = htonl(INADDR_ANY);

    int opt = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if (bind(serverSocket, (sockaddr*)&serverInfo, sizeof(serverInfo)) < 0) {
        perror("bind");
        return;
    }

    if (listen(serverSocket, SOMAXCONN) < 0) {
        perror("listen");
        return;
    }

    Notice("Done setting up the server socket. Handling incoming connections.");

    isStarted = true;

    std::thread([this]() {
        HandleIncomingClients();
    }).detach();
}


void Socket::HandleIncomingClients() {
	while (true) {

		struct sockaddr_in clientInfo;
		socklen_t clientLen = sizeof(clientInfo);

		int clientSocket = accept(serverSocket, (struct sockaddr*) &clientInfo, &clientLen);
        if (clientSocket < 0) {
            Warning("Accepting a connection failed. CODE: " + std::to_string(clientSocket) + " . Ignoring.");
            continue;
        }

		char clientIPBuffer[INET_ADDRSTRLEN]; // buffer for storing client IP addr
		inet_ntop(AF_INET, &clientInfo.sin_addr, clientIPBuffer, INET_ADDRSTRLEN);
		std::string clientIP(clientIPBuffer);

		{
			std::lock_guard<std::mutex> lock(clientMutexHandler);

			clientConnectedCount += 1;
			clientsConnected.push_back(clientIP);
			clientsSocket.push_back(clientSocket);

			// setup client's own thread and detach it
			std::thread threadConnectionHandler(
				&Socket::HandleClientConnection, this, clientsSocket[clientConnectedCount-1], clientIP
			); threadConnectionHandler.detach();

			Notice("Client [ " + std::string(clientIP) + " ] connected. Handling its connection.");
		}

	}
}


void Socket::HandleClientConnection(int clientSocket, std::string clientIP) {
	// send(clientSocket, "ping", 4, 0);

	while (true) {
		char buffer[100];
		int receivedBytes = recv(clientSocket, buffer, sizeof(buffer), 0);

		if (receivedBytes < 0) {
			std::cerr << "[!] Server: Failed to read data sent by IP: " << clientIP << " err code:  " << receivedBytes << "\n";
			// exit(1);
			break;
		}

		if (receivedBytes > 0) {

			buffer[receivedBytes] = '\0';
			std::string message(buffer);

        	std::cout << "From client: " << buffer << '\n';

        	// instance request
			if (message.find("username") != std::string::npos) {
	            send(clientSocket, "ok", 2, 0);
	            std::cout << "Instance request accepted.\n";
			}

        }


        if (receivedBytes == 0) break;
	}


	{
	    clientMutexHandler.lock();
	    clientConnectedCount--;
	    clientsSocket.erase(clientsSocket.begin() + clientSocket);
	    clientMutexHandler.unlock();
	    Warning("Client [ " + clientIP + " ] disconnected.");
    }
    
    close(clientSocket);
}


void Socket::Notice(std::string msg) {
	std::cout << "[+] " + msg << '\n';
}

void Socket::Warning(std::string msg) {
	std::cout << "[!] Warning: " + msg << '\n';
}

void Socket::Error(std::string msg) {
	std::cerr << "[!!] Error: " + msg << '\n';
	exit(1);
}