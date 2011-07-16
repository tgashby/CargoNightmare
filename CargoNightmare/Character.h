/*
	Character class, basis for enemies and the player.

	Author:		Taggart Ashby
*/
#ifndef _CHARACTER_
#define _CHARACTER_

#include <SDL.h>
#include <SDL_image.h>
#include "ImageManager.h"
#include "Point2D.h"

class Character {
public:
	Character(char* f_name, int lvl) : coords(0, 0), level(lvl) {
		setImage(f_name);
	}

	~Character() {}

	//Each enemy may move differently
	virtual void move(Character&);
	//Each enemy will attack differently
	virtual void attack(Character&) = 0;
	//Initialize attack and speed based on level
	virtual void initAttributes(int level) = 0;

	//Image
	SDL_Surface* getImage() const { return image; }

	//Health
	int getHealth() const { return health; }
	void setHealth(int val);
	
	//Attack Strength
	int getAttack() const { return attStr; }

	//Level
	int getLevel() const { return level; }

	//Coords
	Point2D getCoords() { return coords; }
	int getX() const { return coords.getX(); }
	int getY() const { return coords.getY(); }
	float getXVel() const { return xVel; }
	float getYVel() const { return yVel; }

	//Width/Height
	Uint32 getWidth() const { return image->w; }
	Uint32 getHeight() const { return image->h; }

	//Update the speed/health/etc
	virtual void updateAttributes(int);	

protected:
	SDL_Surface* image;
	int health, attStr, level, speed;
	Point2D coords;

	//X and Y "speed"
	float xVel, yVel;
	
	

	void setAttack(int val) {attStr = val;}
	void setImage(const char*);
	void setX(int val) { coords.setX(val); }
	void setY(int val) { coords.setY(val); }
	void setCoords(Point2D newCoords) { coords = newCoords; }
};

#endif
