/*
	Bottle Enemy class

	Author:		Taggart Ashby
*/

#ifndef _BOTTLE_ENEMY_
#define _BOTTLE_ENEMY_

#include "Character.h"

class BottleEnemy : public Character{
public:
	BottleEnemy(char* f_name, int lvl, int xPos, int yPos) : 
	  Character(f_name, lvl) {
		coords.setX(xPos);
		coords.setY(yPos);
		initAttributes(lvl);
	  }

	~BottleEnemy() {
		SDL_FreeSurface(this->getImage());
	}

	//Redefinitions of virtual methods
	void move();
	void attack(Character&);

private:
	void initAttributes(int);
};

#endif
