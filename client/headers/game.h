#include "includes.h"
#include "client.h"

class Game : public Socket {

	int playerX;
	int playerY;

public:
	void Start();

	bool CreateServerSideInstance(std::string name); 

	void PrintMap(int width, int height, int posX, int posY);
	bool HandleBorder(int width, int height, int posX, int posY, int plane, int dir);
	// int PrintMovementSelection(int posX, int posY);
};