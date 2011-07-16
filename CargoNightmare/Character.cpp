#include "Character.h"

void Character::setImage(const char* f_name) {
	image = ImageManager::loadImage(f_name);
}

//Movement for enemies
void Character::move(Character& to) {
	//Set the char's direction
	this->setCoords(this->getCoords().setDirTo(to.getCoords()));

	//Move the char
	this->setX(this->getX() + this->getXVel() * this->getCoords().getXDir());
	this->setY(this->getY() + this->getYVel() * this->getCoords().getYDir());
}

void Character::setHealth(int val) {
		health = val;
}

void Character::updateAttributes(int lvl) {
	this->initAttributes(lvl);
}
