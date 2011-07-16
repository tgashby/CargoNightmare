/*
	Screen Manager, deals with active gamestates and switching between them.

	Author:		Taggart Ashby
*/
#ifndef _SCREEN_MANAGER_
#define _SCREEN_MANAGER_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "ImageManager.h"
#include "Screen.h"

class ScreenManager {
public:
	//Display the menu screen and deal with mouse input
	static bool Menu();

	//Display the help menu, explaining the HUD and controls
	static void Help1();
	static void Help2();

	//Display the silly backstory
	static void Backstory();

	//Display the credits
	static void Credits();

	//Display a level change screen between levels
	static void LevelChange();

	//Display a basic pause screen
	static bool Pause();

	//Display the end screen if you died
	//returns whether or not the user wants to play again
	static bool EndDeath();

	//Display the end screen if you survived
	//returns whether or not the user wants to play again
	static bool EndSuccess();

private:
	static void draw(Screen&);
};

#endif
