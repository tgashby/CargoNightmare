/*
	Screen class

	Author:		Taggart Ashby
*/

#ifndef _SCREEN_
#define _SCREEN_

#include <SDL.h>
#include <SDL_image.h>
#include "LevelManager.h"

class Screen {
public:
	Screen(const char* img_name) {
		screenImg = ImageManager::loadImage(img_name);
		active = true;
	}

	~Screen() {}

	Screen(const Screen& rhs) {
		SDL_FreeSurface(this->screenImg);
		this->screenImg = rhs.screenImg;
		this->activate();
	}
	
	bool isActive() { return active; }
	
	void deactivate() { active = false; }
	void activate() { active = true; }
	
	SDL_Surface* getImage() { return screenImg; }

	operator SDL_Surface*() { return screenImg; }

private:
	SDL_Surface* screenImg;
	bool active;
};


#endif
