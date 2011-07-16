/*
	Weapon class

	Author:		Taggart Ashby
*/
#ifndef _WEAPON_
#define _WEAPON_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
#include <sstream>
#include "ImageManager.h"


class Weapon {
public:
	Weapon(const char* f_name, std::string n, const char* soundName, int pow, 
		int capacity, int clip) {
		
			image = IMG_Load(f_name);
			name = n;
			
			sound = Mix_LoadWAV(soundName);
			
			power = pow;
			
			ammoCapacity = capacity;
			ammoLeft = ammoCapacity;
			
			clipCapacity = clip;
			clipLeft = clipCapacity;

			weapFace = -1;
	}

	~Weapon() {}

	int getPower() { return power; }
	
	//Total Capacities
	int getAmmoCap() { return ammoCapacity; }
	int getClipCap() { return clipCapacity; }
	
	//What is left
	int getAmmoLeft() { return ammoLeft; }
	int getClipLeft() { return clipLeft; }
	
	//Used to change the direction that the weapon is facing
	void setWeapFace(int val) { weapFace = val; }

	bool canFire() { return clipLeft > 0; }
	
	std::string getName() { return name; }
	Mix_Chunk* getSound() { return sound; }
	
	void setImage(const char* f_name);
	SDL_Surface* getImage();

	void reload();
	void fire();
	
	//Put clips and ammo back to full capacity
	void refill();

private:
	SDL_Surface* image;
	std::string name;
	Mix_Chunk* sound;
	int power, ammoCapacity, ammoLeft, clipCapacity, clipLeft;
	int weapFace;

	void setClipLeft(int val) { clipLeft = val; }
	void setAmmoLeft(int val) { ammoLeft = val; }
};

#endif
