#include "includes.h"

class Character {

	int health;
	int damage;

public:
	Character(std::string n, int h, int dmg);

	std::string name;

	void SetHealth(int dmg); // handler for when a character gets damaged
	int GetHealthStatus(); // return current health points
	int GetDamageStatus(); // return current character damage
};