#include "ImageManager.h"

SDL_Surface* ImageManager::loadImage(const char* f_name) {
	//Load the image
	SDL_Surface* img = IMG_Load(f_name);
	
	//If the image doesn't exist, replace it with a dummy image
	if(img == NULL) {
		img = IMG_Load("Resources/images/badImage.jpg");
		return img;
	}

	//Optimize the image
	if(img != NULL) {
		SDL_Surface* optimized = NULL;
		optimized = SDL_DisplayFormat(img);

		SDL_FreeSurface(img);

		return optimized;
	}

	return img;
}

void ImageManager::makeTransparent(SDL_Surface* img) {
	SDL_Color transColor;

	if(img == NULL) return;
	//Use the top left pixel as the color key
	Uint32 pixel = getpixel(img, 0, 0);

	SDL_GetRGB(pixel, img->format, &transColor.r, &transColor.g, &transColor.b);

	SDL_SetColorKey(img, SDL_SRCCOLORKEY, pixel);
}

//Draw an image to an x-y coordinate on the screen
bool ImageManager::draw(SDL_Surface* img, SDL_Surface* dest, int x, int y) {
	SDL_Rect srcRect, destRect;

	srcRect.x = srcRect.y = 0;

	destRect.x = x;
	destRect.y = y;

	srcRect.w = destRect.w = img->w;
	srcRect.h = destRect.h = img->h;

	SDL_BlitSurface(img, &srcRect, dest, &destRect);
	return true;
}

//Draw an image using rectangles
bool ImageManager::drawRect(SDL_Surface* srcImg, SDL_Surface* destImg, SDL_Rect srcRect, SDL_Rect destRect) {
	SDL_BlitSurface(srcImg, &srcRect, destImg, &destRect);
	return true;
}

//Draw a part of an image to a destination
bool ImageManager::drawRect(SDL_Surface* srcImg, SDL_Surface* destImg, SDL_Rect destRect) {
	SDL_BlitSurface(srcImg, &destRect, destImg, &destRect);
	return true;
}

//Free an image
void ImageManager::destroyImage(SDL_Surface* img) {
	SDL_FreeSurface(img);
}

//SDL example, I did not create this
Uint32 ImageManager::getpixel(SDL_Surface *surface, int x, int y) 
{ 
    int bpp = surface->format->BytesPerPixel; 
    /* Here p is the address to the pixel we want to retrieve */ 
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp; 

    switch(bpp) { 
    case 1: 
        return *p; 

    case 2: 
        return *(Uint16 *)p; 

    case 3: 
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) 
            return p[0] << 16 | p[1] << 8 | p[2]; 
        else 
            return p[0] | p[1] << 8 | p[2] << 16; 

    case 4: 
        return *(Uint32 *)p; 

    default: 
        return 0;       /* shouldn't happen, but avoids warnings */ 
    } 
}