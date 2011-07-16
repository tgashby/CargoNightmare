/*
	Ham Sandwich Enemy

	Author:		Taggart Ashby
*/
#ifndef _SANDWICH_ENEMY_
#define _SANDWICH_ENEMY_

#include "Character.h"

class SandwichEnemy : public Character {
public:
	SandwichEnemy(char* f_name, int lvl, int xPos, int yPos) :
	  Character(f_name, lvl) {
		coords.setX(xPos);
		coords.setY(yPos);
		initAttributes(lvl);
	}

	~SandwichEnemy() {
		SDL_FreeSurface(this->getImage());
	}

	//Redefine-ify these
	void attack(Character&);

private:
	void initAttributes(int);
};

#endif
