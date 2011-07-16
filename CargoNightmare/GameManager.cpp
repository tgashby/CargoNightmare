#include "GameManager.h"
#include "Cursor.h"
#include <iostream>

//Constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 675;
const SDL_Color txtCol = { 255, 255, 255 };
const int FPS = 80;
const int GAME_TIME = 300 * 1000;
const int NUM_LEVELS = 5;

//HUD Surfaces
SDL_Surface* upperScreenSurface = NULL;
SDL_Surface* lowerScreenSurface = NULL;
SDL_Surface* newWeapSurface = NULL;

//Cursors
SDL_Cursor* defaultCursor = NULL;
SDL_Cursor* crossHairs = NULL;

//Non-constants
int scoreNum;
bool newWeap = false;

//Timers
int timeLeft;
Uint32 fpsTimer;

bool GameManager::Init() {
	//Set up the main video surface
	display = SDL_GetVideoSurface();

	//Save the cursor
	defaultCursor = SDL_GetCursor();

	//Display the menu
	bool exit = ScreenManager::Menu();
	if(exit) {
		_exit(0);
	}

	//Set up the crosshairs cursor
	crossHairs = SDL_CreateCursor((Uint8*)cursorData,(Uint8*)cursorMask,32,32,15,15);

	//Set the cursor as the crossHairs
	SDL_SetCursor(crossHairs);

	//Initialize the score
	scoreNum = 0;

	//Initialize the timers
	enemyTimer = lvlTimer = SDL_GetTicks();
	timeLeft = (int)lvlTimer + GAME_TIME;

	//Initialize SDL fonts
	TTF_Init();
	font = TTF_OpenFont("Resources/fonts/Secret_Agent_Bold.ttf", 17);

	//Initialize and play music
	music = Mix_LoadMUS("Resources/sounds/Overdriven.ogg");
	Mix_FadeInMusic(music, -1, 1000);

	//Make the outside of the player transparent
	ImageManager::makeTransparent(player.getImage());

	//Draw everything on the screen
	Render();

	//Enable key repeating so that the player can move fluidly.
	SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL);

	SDL_Flip(display);

	GameManager::Update();
	return true;
}

void GameManager::Update() {
	bool running = true;
	

	//Game loop
	while(running) {
		SDL_Event myEvent;
		fpsTimer = SDL_GetTicks();

		if(SDL_PollEvent(&myEvent) == NULL) {
			//No event... do something else?
		} else {
			switch(myEvent.type) {
			
			case SDL_KEYDOWN:
				handleKeyboard(&myEvent);
				break;

			case SDL_MOUSEMOTION:
			case SDL_MOUSEBUTTONDOWN:
				handleMouse(&myEvent);
				break;
			
			case SDL_QUIT:
				running = false;
				break;

			}
		}

		//Deal with the level events
		lvlEvents(lvlTimer);

		//Update the player's position
		player.move();

		//Deal with the enemy events
		enemyEvents(enemyTimer);
		
		//Redraw everything
		Render();

		//If you're dead or time has run out, that's all she wrote
		if(player.isDead() || (timeLeft - SDL_GetTicks()) < 1000) {
			myEvent.type = SDL_QUIT;
			SDL_PushEvent(&myEvent);
		}

		//Regulate the framerate
		if((SDL_GetTicks() - fpsTimer) < 1000 / FPS) {
			SDL_Delay((1000 / FPS) - (SDL_GetTicks() - fpsTimer));
		}
	}

	GameManager::CleanUp();
}

void GameManager::Render() {
	//Draw the level first
	ImageManager::draw(lvlManager.getLvl().getImage(), display, 0, 0);

	//Draw the player and his weapon
	if(player.getXVel() < 0)
		ImageManager::draw(player.getWeap().getImage(), display, 
		(int)(player.getX() - 2.0/3.0 * player.getWeap().getImage()->w), 
		player.getY() + 28 - player.getWeap().getImage()->h / 2);
	else ImageManager::draw(player.getWeap().getImage(), display, 
		player.getX() + (int)(player.getImage()->w - 1.0/3.0 * player.getWeap().getImage()->w),
		player.getY() + 28 - player.getWeap().getImage()->h / 2);

	ImageManager::draw(player.getImage(), display, player.getX(), player.getY());
	

	//Draw the enemies
	enemyManager.drawEnemies();

	//Update/Draw the HUD
	renderHUD();

	SDL_Flip(display);
}

//Shucks, looks like the game is over
void GameManager::CleanUp() {
	bool playAgain;

	Mix_HaltMusic();
	SDL_SetCursor(defaultCursor);

	if(player.isDead())
		playAgain = ScreenManager::EndDeath();
	else playAgain = ScreenManager::EndSuccess();

	if(playAgain) {
		//Re-initialize the enemies
		enemyManager.initialize();

		//Re-initialize the player
		player.initAttributes(1337);
		
		//Re-initialize the levels
		lvlManager.initialize();
		newWeap = false;

		GameManager::Init();
	} else SDL_Quit();
}

void GameManager::handleKeyboard(SDL_Event* myEvent) {

	switch(myEvent->key.keysym.sym) {
	//Player controls
	case SDLK_w:
	case SDLK_a:
	case SDLK_s:
	case SDLK_d:
	case SDLK_r:
	case SDLK_1:
	case SDLK_2:
	case SDLK_3:
		player.keyboardEvent(myEvent);
		break;

	//Fire your weapon
	case SDLK_SPACE:
		//Disable key repeat so that you don't have a machine-gun like pistol/rifle/rpg
		SDL_EnableKeyRepeat(0, 0);

		if(player.getWeap().canFire())
			player.getWeap().fire();
		else break;
		
		//Reenable it for future movement
		SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL);
		
		//Update the score if you hit an enemy
		if(enemyManager.checkCollision(player)) {
			scoreNum += 10 * lvlManager.getLvl().getDifficulty();
		}
		break;

	case SDLK_ESCAPE:
		Uint32 tempTimer = SDL_GetTicks();
		SDL_SetCursor(defaultCursor);
		if(ScreenManager::Pause())
			_exit(0);
		SDL_SetCursor(crossHairs);
		timeLeft += SDL_GetTicks() - tempTimer;
		lvlTimer += SDL_GetTicks() - tempTimer;
		enemyTimer += SDL_GetTicks() - tempTimer;
		break;
	}
}

void GameManager::handleMouse(SDL_Event* myEvent) {
	player.mouseEvent(myEvent);
}

void GameManager::enemyEvents(Uint32& timer) {
	//Spawn an enemy every few seconds
	if(SDL_GetTicks() - timer > 5000 - (unsigned int)(lvlManager.getLvl().getDifficulty() / 2) * 1000) {
		enemyManager.spawn(lvlManager.getLvl().getDifficulty());
		updateTimer(timer);
	}

	//Attack the player roughly every second
	if((SDL_GetTicks() - timer) % 1000 < 10)
		enemyManager.attackPlayer(player);

	enemyManager.update(player);
}

void GameManager::lvlEvents(Uint32& timer) {
	//Disable showing the New Weapon message after 4 seconds
	if(newWeap && SDL_GetTicks() - timer > 4000)
		newWeap = false;

	//Change the level after a certain time
	if(SDL_GetTicks() - timer > (GAME_TIME / NUM_LEVELS)) {
		Uint32 tempTimer = SDL_GetTicks();
		ScreenManager::LevelChange();
		lvlManager.changeLvl();

		//Refill all the player's ammo
		for(int i = 3; i > 0; i--) {
			player.changeWeap(i);
			player.getWeap().refill();
		}

		//Allow the player access to more weapons as they progress
		if(lvlManager.getLvl().getDifficulty() < 4) {
			player.setWeapAccess(lvlManager.getLvl().getDifficulty());
			newWeap = true;
		}

		timeLeft += SDL_GetTicks() - tempTimer;
		enemyTimer += SDL_GetTicks() - tempTimer;
		updateTimer(timer);
	}
}

void GameManager::updateTimer(Uint32& timer) {
	timer = SDL_GetTicks();
}

void GameManager::renderHUD() {
	//Create a buffer between lines
	std::string spaces(13, ' ');
	
	//Set up the top of the screen
	std::stringstream upperStream;
	upperStream << "Score: " << scoreNum << spaces << "Time Remaining: " 
		<< (timeLeft - SDL_GetTicks()) / 1000 << " seconds";

	//Set up the bottom of the screen
	std::stringstream lowerStream;
	lowerStream << "Health: " << player.getHealth() << spaces << "Weapon: ";
	
	//Resize padding for semi-consistent bottom bar
	spaces.resize(spaces.length() + 5 - player.getWeap().getName().length(), ' ');
	lowerStream << player.getWeap().getName() << spaces << "Clip: ";

	lowerStream << player.getWeap().getClipLeft() << "  Ammo: " << player.getWeap().getAmmoLeft();

	//Render the text and draw it
	upperScreenSurface = TTF_RenderText_Solid(font, upperStream.str().c_str(), txtCol);
	ImageManager::draw(upperScreenSurface, display, 10, 0);
	SDL_FreeSurface(upperScreenSurface);
	
	lowerScreenSurface = TTF_RenderText_Solid(font, lowerStream.str().c_str(), txtCol);
	ImageManager::draw(lowerScreenSurface, display, 10, SCREEN_HEIGHT - 30);
	SDL_FreeSurface(lowerScreenSurface);

	//If it is within a few seconds of a new level, 
	// make sure the player knows they can access more weapons
	if(newWeap) {
		newWeapSurface = TTF_RenderText_Solid(font, "NEW WEAPON!!!", txtCol);
		ImageManager::draw(newWeapSurface, display, 300, SCREEN_HEIGHT - 70);
		SDL_FreeSurface(newWeapSurface);
	}
}