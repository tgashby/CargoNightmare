/*
	Static class to deal with images, loading, optimizing, and blitting.

	Author:		Taggart Ashby
*/

#ifndef _IMAGE_MANAGER_
#define _IMAGE_MANAGER_

#include <SDL.h>
#include <SDL_image.h>

class ImageManager {
public:
	//Load an image from a file, optimize it, and return the surface
	static SDL_Surface* loadImage(const char* f_name);
	
	//Makes an image transparent, uses the color of the upper left-hand corner for
	//the color key
	static void makeTransparent(SDL_Surface*);
	
	//Blitting functions
	static bool draw(SDL_Surface* image, SDL_Surface* destination, int x_pos, int y_pos);
	static bool drawRect(SDL_Surface* srcImg, SDL_Surface* destImg, SDL_Rect src, SDL_Rect dest);
	static bool drawRect(SDL_Surface* srcImg, SDL_Surface* destImg, SDL_Rect dest);
	
	//Image cleanup
	static void destroyImage(SDL_Surface*);
	
private:
	static Uint32 getpixel(SDL_Surface*, int x, int y);
};

#endif
