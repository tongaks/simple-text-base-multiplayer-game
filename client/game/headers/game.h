
class Game {

public:
	void PrintMap(int width, int height, int playerX, int playerY);
	int PrintMovementSelection(int posX, int posY);
	bool HandleBorder(int width, int height, int posX, int posY, int plane, int dir);
};