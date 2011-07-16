#include "PenEnemy.h"

void PenEnemy::attack(Character& player) {
	player.setHealth(player.getHealth() - this->getAttack());
}

//Initialize a Pen with attributes based on the level
void PenEnemy::initAttributes(int lvl) {	
	this->xVel = (int)(lvl/3) + 1.0f;
	this->yVel = (int)(lvl/3) + 1.0f;

	this->attStr = lvl / 2 * 3 + 1;

	this->health = lvl / 2 * 15;
}