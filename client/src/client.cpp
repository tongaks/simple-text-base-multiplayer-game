#include "../headers/client.h"

void Socket::SetupSocket() {
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("socket");
        exit(1);
    }

    serverInfo.sin_family = AF_INET;
    serverInfo.sin_port = htons(SERVER_PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serverInfo.sin_addr) <= 0) {
        perror("inet_pton");
        close(clientSocket);
        exit(1);
    }
}

void Socket::ConnectToTheServer() {
    if (connect(clientSocket, (struct sockaddr*)&serverInfo, sizeof(serverInfo)) < 0) {
        perror("connect");
        close(clientSocket);
        exit(1);
    }

    std::cout << "Connected to server on port 3423\n";
}

void Socket::SendToServer() {
    const char* message = "Hello from C++ client";
    send(clientSocket, message, strlen(message), 0);
}

void Socket::ListenToServer() {
	char buffer[BUFFER_SIZE];

    ssize_t bytes = recv(clientSocket, buffer, BUFFER_SIZE - 1, 0);
    if (bytes > 0) {
        buffer[bytes] = '\0';
        std::cout << "Server: " << buffer << std::endl;
    }
}