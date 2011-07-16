/*
	Level Manager, deals with changing levels

	Author:		Taggart Ashby
*/

#ifndef _LEVEL_MANAGER_
#define _LEVEL_MANAGER_

#include <SDL.h>
#include <SDL_image.h>
#include <sstream>
#include "Level.h"

class LevelManager {

public:
	LevelManager(char* img_name) : currLevel(img_name, 1) {}

	Level getLvl() { return currLevel; }

	void changeLvl();

	//Re-initialize the Level Manager for game restarts
	void initialize();

private:
	void setLvl(Level& newLvl) { currLevel = newLvl; }
	Level currLevel;
};

#endif
