#include "includes.h"

class Character {

	std::string name;
	int health;
	int damage;

public:
	Character(std::string n, int h, int dmg);

	void SetHealth(int dmg); // handler for when a character gets damaged
	int GetHealthStatus(); // return current health points
	int GetDamageStatus(); // return current character damage
};