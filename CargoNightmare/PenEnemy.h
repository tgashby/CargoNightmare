/*
	Pen Enemy class

	Author:		Taggart Ashby
*/
#ifndef _PEN_ENEMY_
#define _PEN_ENEMY_

#include "Character.h"

class PenEnemy : public Character{
public:
	PenEnemy(char* f_name, int lvl, int xPos, int yPos) :
	  Character(f_name, lvl) {
		coords.setX(xPos);
		coords.setY(yPos);
		initAttributes(lvl);
	}

	~PenEnemy() {
		SDL_FreeSurface(this->getImage());
	}

	//Redefinitions
	void move();
	void attack(Character&);

private:
	void initAttributes(int);
};

#endif
