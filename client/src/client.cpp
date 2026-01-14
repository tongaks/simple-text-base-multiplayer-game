#include "../headers/client.h"

void Socket::SetupSocket(int& cSocket, sockaddr_in &server, int port) {
    // clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    cSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (cSocket < 0) {
        perror("[!] cSocket: ");
        exit(1);
    }

    // clear
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (inet_pton(AF_INET, "127.0.0.1", &server.sin_addr) <= 0) {
        perror("[!!] inet_pton");
        close(cSocket);
        exit(1);
    }

    printw("[+] Done setting up the socket.\n");
    refresh();
}


// new
// one function connection
// void Socket::ConnectToServerPort(int& cSocket, sockaddr_in &addr) {
//     if (connect(cSocket, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
//         perror("[!!] Error on connecting to server");
//         close(mainClientSocket);
//         exit(1);
//     }

//     std::string format = "[+] Connected to server on port [" + std::to_string(MAIN_SERVER_PORT) + "]\n";
//     printw(format.c_str());
//     refresh();
// }

void Socket::ConnectToMainServer() {
    if (connect(mainClientSocket, (struct sockaddr*)&serverMainInfo, sizeof(serverMainInfo)) < 0) {
        perror("[!!] Error on connecting to main server: ");
        close(mainClientSocket);
        exit(1);
    }

    isConnectedToMain = true;
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

    isConnected = true;
}


void Socket::SendToServer(int& cSocket, std::string msg) {
    // const char* info = (msg + '\0').c_str();
    size_t msgLength = msg.length();
    int res = send(cSocket, msg.c_str(), msgLength, 0);

    if (res < 0) {
        perror("[!] Send error");
        refresh();
    }
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