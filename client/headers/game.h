#include "includes.h"
#include "client.h"
#include "character.h"

struct Player {
	std::string playerName;
	int playerX, playerY;

	void Setup(std::string n, int pX, int pY) {
		this->playerName = n;
		this->playerX = pX;
		this->playerY = pY;
	}
};

struct MapInfo {
	// old 
	// int exitPosX, exitPosY;
	// int playerPosX, playerPosY;
	// int mapW, mapH;


	// new
	std::vector<Player> currentPlayers;
	int exitX, exitY;
	int mapW, mapH;

	void Setup(int w, int h, int x, int y, Player p) {
		this->mapW = w;
		this->mapH = h;
		this->exitX = x;
		this->exitY = y;

		currentPlayers.push_back(p);
	}
};


class Game : public Socket, public Character {
	int playerX, playerY;

public:

	std::string playerName;
	int selectedServerPort = 0;
	std::string rawMapData;

	MapInfo ParseMap(std::string mapInfo);
	MapInfo GetMapInfo(std::string mapInfo);
	void UpdateCoord(std::string msg, MapInfo& map);

	void Start();
	bool CreateServerSideInstance(std::string name); 

	void ListenForNewPlayers(MapInfo& map);


	void PrintMap(int width, int height, MapInfo map);
	bool HandleBorder(int width, int height, int posX, int posY, int plane, int dir);

	int GetServerList();
	void PrintServerListMenu(std::vector<std::string> serverList, int currentSelected);
};