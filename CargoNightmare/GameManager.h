/*
	Header for singleton class to deal with the mechanics of the game

	Author:		Taggart Ashby
*/

#ifndef _GAME_MANAGER_
#define _GAME_MANAGER_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <sstream>
#include "Screen.h"
#include "ImageManager.h"
#include "ScreenManager.h"
#include "EnemyManager.h"
#include "Player.h"
#include "Enemies.h"
#include "LevelManager.h"

#define GMan GameManager::Instance()

class GameManager {
public:
	static GameManager& Instance() {
		static GameManager gMan;
		return gMan;
	}

	~GameManager() {}

	void Start() { GameManager::Init(); }

	//Basic game-loop functionality
	bool Init();
	void Update();
	void CleanUp();

	//Input handling
	void handleKeyboard(SDL_Event*);
	void handleMouse(SDL_Event*);
	
	//Event handling
	void enemyEvents(Uint32&);
	void lvlEvents(Uint32&);
	
	//Reset/Update a timer
	void updateTimer(Uint32&);
	
	//Render all the text on the screen
	void renderHUD();

private:
	GameManager() : display(NULL), player("Resources/player/playerLft.png"), 
		lvlManager("Resources/levels/room_0.png") {}

	//Rendering of the HUD
	void Render();

	//The main display surface
	SDL_Surface* display;

	Player player;
	TTF_Font* font;
	Mix_Music* music;
	
	//Managers
	LevelManager lvlManager;
	EnemyManager enemyManager;

	//Timers
	Uint32 enemyTimer, lvlTimer;	
};

#endif
