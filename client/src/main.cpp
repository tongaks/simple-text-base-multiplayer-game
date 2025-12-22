#include "../headers/client.h"

int main(int argc, char const *argv[]) {
	Socket sock1;
	sock1.SetupSocket();
	sock1.ConnectToTheServer();
	sock1.SendToServer();
	// sock1.ListenToServer();
	return 0;
}