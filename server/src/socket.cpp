#include "../headers/socket.h"

void Socket::CreateSockets(int count) {
	srand(time(0));
	for (int i = 0; i < count; i++) {

		int port;
		while (1) {
			port = std::rand() % (9999 + 1 - 4000) + 4000;
			if (port != MAIN_SERVER_PORT) break;
		}

		serverPortList.push_back(std::to_string(port));
		Notice("Port: " + std::to_string(port) + " created.");
		uServerSockets.emplace_back(std::make_unique<ServerSocket>(port));
	}

	// set up after pushing the ServerSocket
	for (const auto& ss : uServerSockets) {
		SetupSocket(*ss);
		ss->map = GenerateMap(MAPW, MAPH);
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
    // isStarted = true;

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

			std::thread ([this, index = ss.clientCount, &ss]() {
			    HandleClientConnection(ss, index);
			}).detach();

			ss.clientCount += 1;
			ss.clientsIP.push_back(clientIP);
			ss.clientsSocket.push_back(clientSocket);

			Notice("From: [" + std::to_string(ss.port) + "]: Client [ " + std::string(clientIP) + " ] connected. Handling its connection.");
		}
	}
}

// void Socket::HandleClientConnection(ServerSocket &ss, std::string port, int clientSocket, std::string clientIP) {
void Socket::HandleClientConnection(ServerSocket &ss, int index) {
	while (true) {
		char buffer[101];
		int receivedBytes = recv(ss.clientsSocket[index], buffer, sizeof(buffer) - 1, 0);
		buffer[receivedBytes] = '\0';

		if (receivedBytes < 0) {
			perror("[!!] Recv Error");
			std::cerr << "[!] Server port [" << ss.port << "]: Failed to read data sent by IP: " << ss.clientsIP[index] << " err code:  " << receivedBytes << "\n";
			break;
		} else if (receivedBytes == 0) {
			std::cout << "A Client disconnected.\n";
			break;
		}


		if (receivedBytes > 0) {
			std::string message(buffer);
			Notice("[" + std::to_string(ss.port) + "] client: " + buffer);

			if (message.find("username") != std::string::npos) {
				int startPos = message.find(":");
				std::string pName = message.substr(startPos+1, message.length()); 

				Player pTemp = CreatePlayer(pName, ss.map);
				ss.currentPlayers.push_back(pTemp);				// store the player
				Notice("Player: " + pName + " created.");

				// old
				// MapInfo mapPos = GenerateMap(MAPW, MAPH);
				// std::string exitXY = std::to_string(mapPos.exitX) + " " + std::to_string(mapPos.exitY);
				// std::string exitXY = std::to_string(ss.map.exitX) + " " + std::to_string(ss.map.exitY);
				// std::string playerCoord = std::to_string(pTemp.posX) + " " + std::to_string(pTemp.posY);
				// std::string strMap = playerCoord + " " + exitXY;


				// new: for client new ParseInitialMap
				std::string exitXY = std::to_string(ss.map.exitX) + "," + std::to_string(ss.map.exitY);
				std::string playerCoord = std::to_string(pTemp.posX) + "," + std::to_string(pTemp.posY);
				std::string mapSize = std::to_string(ss.map.mapW) + "," + std::to_string(ss.map.mapH);
				std::string strMap = "map.info:" + mapSize + "," + exitXY + "," + playerCoord;


				Notice("Sending coordinates: " + strMap + " to client.");
				int mapPosStrLength = strMap.length();
				send(ss.clientsSocket[index], strMap.c_str(), mapPosStrLength, 0);
				Notice("Map sent.");

				// update other clients, only if there's more than 1 players
				if (ss.clientsSocket.size() > 1) {
					Notice("Updating clients about the new player.");

					std::string updateClients = pName + ".coord:" + playerCoord;
					int iterator = 0;
					for (int& client : ss.clientsSocket) {
						if (iterator == index) continue;
						send(client, updateClients.c_str(), updateClients.length(), 0);
					}
				}


			} else if (message.find("servers") != std::string::npos) {
				Notice("Client requested server lists");

				std::string temp = "";
				for (std::string s : serverPortList) temp += s + " ";
				Notice("Sending ports: " + temp + " to the client.");
				send(ss.clientsSocket[index], temp.c_str(), temp.size(), 0);

				
				// handler for when client sent a update coord
			} else if (message.find("coord") != std::string::npos) {

				int x, y;
				char name[50];
				if (sscanf(message.c_str(), "%[^.].coord:%d,%d", name, &x, &y) == 3) {

					std::string exitXY, playerCoord, strMap;
					for (auto& p : ss.currentPlayers) {
						if (name == p.playerName) {
							p.posX = x;
							p.posY = y;

							exitXY = std::to_string(ss.map.exitX) + " " + std::to_string(ss.map.exitY);
							playerCoord = std::to_string(p.posX) + " " + std::to_string(p.posY);
							strMap = playerCoord + " " + exitXY;
						}
					}

					// todo: update client code to handle this
					// send to all client the newly updated position of a player
					int mapPosStrLength = strMap.length();
					for (int& client : ss.clientsSocket) {
						send(client, strMap.c_str(), mapPosStrLength, 0);
					}


				}
			}
        }

		// Notice("Sending coordinates: " + strMap + " to client.");
		// Notice("Map sent.");
		// Notice("Map sent to player: " + p.playerName);
	}


	{
	    std::lock_guard<std::mutex> lock(ss.clientMutex);

		// int clientSocket = ss.clientsSocket[index];
		close(ss.clientsSocket[index]);
		ss.clientsSocket.erase(ss.clientsSocket.begin() + index);
		ss.clientCount--;

	    std::string format = "[" + std::to_string(ss.port) +"] client [ " + ss.clientsIP[index] + " ]: disconnected.";
	    Warning(format);
    }
    
    close(ss.clientsSocket[index]);
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