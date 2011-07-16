#include "SandwichEnemy.h"

void SandwichEnemy::attack(Character& player) {
	player.setHealth(player.getHealth() - this->getAttack());
}

//Initialize a Sandwich with attributes based on the level
void SandwichEnemy::initAttributes(int lvl) {
	this->xVel = (int)(lvl/4) + 1.0f;
	this->yVel = (int)(lvl/4) + 1.0f;

	this->attStr = lvl / 2 * 6 + 1;

	this->health = lvl / 2 * 30;
}
