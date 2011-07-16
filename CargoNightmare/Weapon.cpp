#include "Weapon.h"

void Weapon::setImage(const char* f_name) {
	image = ImageManager::loadImage(f_name);
	ImageManager::makeTransparent(image);
}

SDL_Surface* Weapon::getImage() {
	std::stringstream imgStream;

	imgStream << "Resources/weapons/" << this->getName();

	if(weapFace < 0)
		imgStream << "Lft.png";
	else imgStream << "Rt.png";

	this->setImage(imgStream.str().c_str());

	return image;
}

void Weapon::reload() {
	//Figure out amount of ammo that needs to be moved to the clip
	int ammoTransfer = this->getClipCap() - this->getClipLeft();

	//Deal with the case when ammo left is less than clip capacity
	if(this->getAmmoLeft() < ammoTransfer) {
		this->setClipLeft(this->getClipLeft() + this->getAmmoLeft());
		this->setAmmoLeft(0);
	} else {
		this->setAmmoLeft(this->getAmmoLeft() - ammoTransfer);
		this->setClipLeft(this->getClipCap());
	}
}

void Weapon::fire() {
	//Remove one bullet from the clip
	this->setClipLeft(this->getClipLeft() - 1);

	//Play the gun sound
	Mix_PlayChannel(-1, this->getSound(), 0);
}

void Weapon::refill() {
	this->setClipLeft(this->getClipCap());
	this->setAmmoLeft(this->getAmmoCap());
}