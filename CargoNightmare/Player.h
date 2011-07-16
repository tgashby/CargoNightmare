/*
	Player class

	Author:		Taggart Ashby
*/
#ifndef _PLAYER_
#define _PLAYER_

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Character.h"
#include "Weapon.h"
#include "ImageManager.h"

class Player : public Character {
public:
	Player(char* f_name) : Character(f_name, 1337) {
		health = 250;
		
		xVel = 10;
		yVel = 10;
		this->setX(400);
		this->setY(380);

		//The player can only access certain weapons at a time
		currWeap = weapAccess = 1;

		//Add all the weapons to the player's arsenal
		Weapon pistol("Resources/weapons/PistolLft.png", "Pistol", 
			"Resources/sounds/pistol.wav", 5, 50, 15);
		Weapon laserRifle("Resources/weapons/Laser RifleLft.png", "Laser Rifle", 
			"Resources/sounds/laserRifle.wav", 15, 30, 5);
		Weapon rpg("Resources/weapons/Rpg.png", "RPG", 
			"Resources/sounds/rpg.wav", 100, 7, 1);
		weaps.push_back(pistol);
		weaps.push_back(laserRifle);
		weaps.push_back(rpg);
	}

	~Player() {
		SDL_FreeSurface(image);
	}

	void keyboardEvent(SDL_Event*);
	void mouseEvent(SDL_Event*);
	
	void move();
	
	//This doesn't do anything in this game
	void attack(Character&) {}

	//Reinitialize the player for game restarts
	void initAttributes(int);
	
	
	//Check health
	bool isDead() { return health <= 0; }
	
	//Weapons manipulation
	void addWeap(Weapon newWeap);
	void changeWeap(int);
	Weapon& getWeap() { return weaps.at(currWeap - 1); }

	//Change the player's access to his arsenal
	void setWeapAccess(int newAccess) { weapAccess = newAccess; }

private:
	//Keeps all the weapons
	std::vector<Weapon> weaps;
	
	int currWeap, weapAccess;
};

#endif
