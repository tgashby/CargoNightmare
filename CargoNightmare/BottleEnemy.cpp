#include "BottleEnemy.h"

void BottleEnemy::attack(Character& player) {
	player.setHealth(player.getHealth() - this->getAttack());
}

//Initialize a Bottle with attributes based on the level
void BottleEnemy::initAttributes(int lvl) {
	this->xVel = (float)lvl;
	this->yVel = (float)lvl;

	this->attStr = lvl / 2 * 2 + 1;

	this->health = lvl / 2 * 10;
}