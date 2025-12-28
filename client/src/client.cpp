#include "../headers/client.h"

void Socket::SetupSocket(int port) {
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("socket");
        exit(1);
    }

    serverInfo.sin_family = AF_INET;
    serverInfo.sin_port = htons(port);

    if (inet_pton(AF_INET, "127.0.0.1", &serverInfo.sin_addr) <= 0) {
        perror("inet_pton");
        close(clientSocket);
        exit(1);
    }
}

void Socket::ConnectToTheServer() {
    if (connect(clientSocket, (struct sockaddr*)&serverInfo, sizeof(serverInfo)) < 0) {
        perror("[!] Connect");
        close(clientSocket);
        exit(1);
    }

    printw("[+] Connected to the server on port 3423\n");
    refresh();

    isConnected = true;
}


void Socket::SendToServer(std::string msg) {
    const char* info = msg.c_str();
    send(clientSocket, info, strlen(info), 0);
}


std::string Socket::ListenToServer() {
	char buffer[BUFFER_SIZE];
    std::string msg(buffer);

    ssize_t bytes = recv(clientSocket, buffer, BUFFER_SIZE - 1, 0);
    if (bytes > 0) {
        buffer[bytes] = '\0';
        return std::string(buffer);
    } else return "err";
}