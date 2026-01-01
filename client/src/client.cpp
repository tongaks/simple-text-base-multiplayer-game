#include "../headers/client.h"

void Socket::SetupSocket(int& cSocket, sockaddr_in &server, int port) {
    // clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    cSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (cSocket < 0) {
        perror("[!] cSocket: ");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (inet_pton(AF_INET, "127.0.0.1", &server.sin_addr) <= 0) {
        perror("inet_pton");
        close(cSocket);
        exit(1);
    }
}


void Socket::ConnectToMainServer() {
    if (connect(mainClientSocket, (struct sockaddr*)&serverMainInfo, sizeof(serverMainInfo)) < 0) {
        perror("[!!] Error on connecting to main server: ");
        close(clientSocket);
        exit(1);
    }

    std::string format = "[+] Connected to main server on port [" + std::to_string(MAIN_SERVER_PORT) + "]\n";
    printw(format.c_str());
    refresh();
}


void Socket::ConnectToTheServer() {
    if (connect(clientSocket, (struct sockaddr*)&serverInfo, sizeof(serverInfo)) < 0) {
        perror("[!] Connect");
        close(clientSocket);
        exit(1);
    }

    // printw("[+] Connected to the server on port [%s]\n", std::to_string(selectedServerPort));
    printw("[+] Connected to the server on port\n");
    refresh();
}


void Socket::SendToServer(int& cSocket, std::string msg) {
    const char* info = msg.c_str();
    send(cSocket, info, strlen(info), 0);
}


std::string Socket::ListenToServer(int& cSocket) {
	char buffer[BUFFER_SIZE];
    std::string msg(buffer);

    ssize_t bytes = recv(cSocket, buffer, BUFFER_SIZE - 1, 0);
    if (bytes > 0) {
        buffer[bytes] = '\0';
        return std::string(buffer);
    } else return "err";
}