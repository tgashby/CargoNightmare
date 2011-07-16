/*
	Cargo Nightmare
		A third-person shooter.

	Created using SDL 1.2

	Author:		Taggart Ashby
*/

#include "GameManager.h"

int main(int argc, char* argv[]) {
	//Initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return false;
	}

	//Set icon and captions
	SDL_WM_SetIcon(SDL_LoadBMP("Resources/images/icon.bmp"), NULL);
	SDL_WM_SetCaption("Cargo Nightmare", "Cargo Nightmare");

	//Set up the window size
	SDL_SetVideoMode(800, 675, 0, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_NOFRAME);
	
	//Initialzie mixer (for sounds)
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

	//Game Loop
	GMan.Start();
	
	return 0;
}