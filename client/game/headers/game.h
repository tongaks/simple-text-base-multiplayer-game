#include <iostream>
#include <vector>
#include <ncurses.h>

class Game {

	int playerX;
	int playerY;

public:
	void Start();
	void PrintMap(int width, int height, int posX, int posY);
	bool HandleBorder(int width, int height, int posX, int posY, int plane, int dir);
	// int PrintMovementSelection(int posX, int posY);
};