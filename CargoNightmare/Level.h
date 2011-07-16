/*
	Level class, pretty self-explanatory :-P

	Author:		Taggart Ashby
*/

#ifndef _LEVEL_
#define _LEVEL_

#include <SDL.h>
#include <SDL_image.h>
#include "ImageManager.h"

class Level {
public:
	Level(const char* img_name, int diff) {
		image = ImageManager::loadImage(img_name);
		difficulty = diff;
	}

	//Copy constructor
	Level(const Level& lvl) {
		image = lvl.getImage();
		difficulty = lvl.getDifficulty();
	}

	~Level() {}

	//Getters
	SDL_Surface* getImage() const {return image;}
	int getDifficulty() const {return difficulty;}

private:
	SDL_Surface* image;
	int difficulty;
};

#endif
