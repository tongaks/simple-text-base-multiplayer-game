#include "../headers/socket.h"
#include "../headers/game.h"

// to do: set up multiple sockets

void Socket::CreateSockets(int count) {

	// generate random port
	srand(time(0));
	for (int i = 0; i < count; i++) {
		int port = std::rand() % (9999 + 1 - 4000) + 4000;
		Notice("Port: " + std::to_string(port) + " created.");
		uServerSockets.emplace_back(std::make_unique<ServerSocket>(port));
	}

	// set up after pushing the ServerSocket
	for (const auto& ss : uServerSockets) {
		SetupSocket(*ss);
	}

}


void Socket::SetupSocket(ServerSocket &ss) {
	ss.socket = socket(AF_INET, SOCK_STREAM, 0);

    ss.serverInfo.sin_family = AF_INET;
    ss.serverInfo.sin_port = htons(ss.port);
    ss.serverInfo.sin_addr.s_addr = htonl(INADDR_ANY);

    int opt = 1;
    setsockopt(ss.socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if (bind(ss.socket, (sockaddr*)&ss.serverInfo, sizeof(ss.serverInfo)) < 0) {
        perror("[!!] bind");
        return;
    }

    if (listen(ss.socket, SOMAXCONN) < 0) {
        perror("[!!] listen");
        return;
    }

    Notice("Done setting up the server port [" + std::to_string(ss.port) + "]. Handling incoming connections.");
    isStarted = true;

    std::thread ([this, &ss]() {
        HandleIncomingClients(ss);
    }).detach();
}


void Socket::HandleIncomingClients(ServerSocket &ss) {
	while (true) {

		struct sockaddr_in clientInfo;
		socklen_t clientLen = sizeof(clientInfo);

		int clientSocket = accept(ss.socket, (struct sockaddr*) &clientInfo, &clientLen);
        if (clientSocket < 0) continue;

		char clientIPBuffer[INET_ADDRSTRLEN]; // buffer for storing client IP addr
		inet_ntop(AF_INET, &clientInfo.sin_addr, clientIPBuffer, INET_ADDRSTRLEN);
		std::string clientIP(clientIPBuffer);

		{
			std::lock_guard<std::mutex> lock(ss.clientMutex);

			ss.clientCount += 1;
			ss.clientsIP.push_back(clientIP);
			ss.clientsSocket.push_back(clientSocket);

			std::thread ([
					this, 
					port = std::to_string(ss.port), 
			        socket = clientSocket, 
			        ip = clientIP,
			        &ss]() {
			    HandleClientConnection(ss, port, socket, ip);
			}).detach();


			Notice("From: [" + std::to_string(ss.port) + "]: Client [ " + std::string(clientIP) + " ] connected. Handling its connection.");
		}

	}
}


void Socket::HandleClientConnection(ServerSocket &ss, std::string port, int clientSocket, std::string clientIP) {

	while (true) {
		char buffer[100];
		int receivedBytes = recv(clientSocket, buffer, sizeof(buffer), 0);

		if (receivedBytes < 0) {
			std::cerr << "[!] Server port [" << port << "]: Failed to read data sent by IP: " << clientIP << " err code:  " << receivedBytes << "\n";
			break;
		}

		if (receivedBytes > 0) {

			buffer[receivedBytes] = '\0';
			std::string message(buffer);
			Notice("[" + port + "] client: " + buffer);

        	// instance request
			if (message.find("username") != std::string::npos) {
				std::string mapPos = GenerateMap(MAPW, MAPH); // send player coord
				int mapPosStrLength = mapPos.length();
				send(clientSocket, mapPos.c_str(), mapPosStrLength, 0);
				Notice("Instance accepted.");
			} else if (message.find("servers")) {
				// return list of server sockets
			}
        }

        if (receivedBytes == 0) break;
	}


	{
	    std::lock_guard<std::mutex> lock(ss.clientMutex);
	    ss.clientCount--;
	    ss.clientsSocket.erase(ss.clientsSocket.begin() + clientSocket);
	    Warning("[" + port +"] client [ " + clientIP + " ]: disconnected.");
    }
    
    close(clientSocket);
}

std::string Socket::GenerateMap(int width, int height) {
	int playerPosX = std::rand() % (width - 2);
	int playerPosY = std::rand() % (height - 2);

	int exitX = 0;
	int exitY = 0;
	while (1) {
		exitX = std::rand() % (width - 2);
		exitY = std::rand() % (height - 2);
		if (exitX != playerPosX && exitY != playerPosY) break;
	}

	std::string playerPos = std::to_string(playerPosX) + " " + std::to_string(playerPosY);
	std::string exitPos = std::to_string(exitX) + " " + std::to_string(exitY);
	Notice("Map: " + playerPos + " " + exitPos);

	return playerPos + " " + exitPos;
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