#include "includes.h"
#include "client.h"
#include "character.h"

class Game : public Socket, public Character {

	int playerX;
	int playerY;

public:

	struct MapInfo {
		int playerPosX;
		int playerPosY;

		int exitPosX;
		int exitPosY;
	};

	MapInfo ParseMap(std::string mapInfo);

	std::string rawMapData;

	void Start();
	bool CreateServerSideInstance(std::string name); 

	void PrintMap(int width, int height, MapInfo map);
	bool HandleBorder(int width, int height, int posX, int posY, int plane, int dir);

	void GetServerList();
	// int PrintMovementSelection(int posX, int posY);
};