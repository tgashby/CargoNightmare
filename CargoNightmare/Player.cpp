#include "Player.h"

void Player::keyboardEvent(SDL_Event* myEvent) {
	switch(myEvent->key.keysym.sym) {
		//Movement
		case SDLK_w:
			this->setY(this->getY() - 10);
			break;

		case SDLK_s:
			this->setY(this->getY() + 10);
			break;

		case SDLK_a:
			this->setX(this->getX() - 10);
			break;

		case SDLK_d:
			this->setX(this->getX() + 10);
			break;
		//

		//Reloarding
		case SDLK_r:
			SDL_EnableKeyRepeat(0, 0);
			SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL);

			this->getWeap().reload();
			break;
			
		//Weapon selection
		case SDLK_1:
			this->changeWeap(1);
			break;

		case SDLK_2:
			if(weaps.size() >= 2)
				this->changeWeap(2);
			break;

		case SDLK_3:
			if(weaps.size() >= 3)
				this->changeWeap(3);
			break;
		//
	}
}

void Player::mouseEvent(SDL_Event* myEvent) {
	int x;
	SDL_Surface* img = NULL;

	SDL_GetMouseState(&x, NULL);

	//Flip the player around depending on where the user is aiming
	if(x < this->getX()) {
		this->xVel = -1;
		this->getWeap().setWeapFace(-1);

		this->setImage("Resources/player/playerLft.png");
		ImageManager::makeTransparent(this->getImage());
	} else {
		this->xVel = 1;
		this->getWeap().setWeapFace(1);

		this->setImage("Resources/player/playerRt.png");
		ImageManager::makeTransparent(this->getImage());
	}
}

void Player::move() {
	//Make sure the player doesn't leave the room
	if(this->getX() > 670)
		this->setX(670);
	else if(this->getX() < 100)
		this->setX(100);

	//Make sure the player doesn't climb on the walls
	if(this->getY() > 595)
		this->setY(595);
	else if(this->getY() < 210)
		this->setY(210);
}

//Never used in this game
void Player::addWeap(Weapon newWeap) {
	weaps.push_back(newWeap);
}

//If allowed, change weapon
void Player::changeWeap(int weapNdx) {
	if(weapNdx <= weapAccess) 
		currWeap = weapNdx; 
}

void Player::initAttributes(int unused) {
	for(int i = 1; i < 4; i++) {
		this->changeWeap(i);
		this->getWeap().refill();
	}

	this->changeWeap(1);
	this->setWeapAccess(1);

	this->setHealth(250);
}