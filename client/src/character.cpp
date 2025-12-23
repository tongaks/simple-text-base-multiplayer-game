#include "../headers/game.h"

// sent client info to server
// then server create its own object 
// base on the client sent info 

Character::Character(std::string n, int h, int dmg) {
	this->name = n;
	this->health = h;
	this->damage = dmg;
}

void Character::SetHealth(int dmg) {
	this->health -= dmg;
}

int Character::GetHealthStatus() {
	return this->health;
}

int Character::GetDamageStatus() {
	return this->damage;
}