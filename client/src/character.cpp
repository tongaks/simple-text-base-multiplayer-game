#include "../headers/character.h"

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