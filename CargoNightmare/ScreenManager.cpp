#include "ScreenManager.h"

bool ScreenManager::Menu() {
	bool end = false;
	int mouseX, mouseY;

	Screen menuScreen("Resources/images/menu.png");
	draw(menuScreen);

	while(menuScreen.isActive()) {
		SDL_GetMouseState(&mouseX, &mouseY);
		SDL_Event myEvent;

		if(SDL_PollEvent(&myEvent) && myEvent.type == SDL_MOUSEBUTTONDOWN)
			if(mouseY > 295 && mouseY < 471) {
				//If the user chooses "Play"
				if(mouseX < 255 && mouseX > 145) 
					menuScreen.deactivate();

				if(mouseX < 396 && mouseX > 286) {
					ScreenManager::Backstory();
					draw(menuScreen);
				}

				if(mouseX < 539 && mouseX > 429) {
					ScreenManager::Help1();
					draw(menuScreen);
				}

				if(mouseX < 621 && mouseX > 571) {
					ScreenManager::Credits();
					draw(menuScreen);
				}

				//If the player chooses "Exit"
				if(mouseX < 684 && mouseX > 634) {
					end = true;
					menuScreen.deactivate();
				}
		}
	}

	return end;
}

void ScreenManager::Help1() {
	int mouseX, mouseY;

	Screen helpScreen("Resources/images/help1.png");
	draw(helpScreen);

	while(helpScreen.isActive()) {
		SDL_GetMouseState(&mouseX, &mouseY);
		SDL_Event myEvent;

		if(SDL_PollEvent(&myEvent) && myEvent.type == SDL_MOUSEBUTTONDOWN)
			if(mouseX > 605 && mouseX < 770 && mouseY > 540 && mouseY < 625) {
				ScreenManager::Help2();
				helpScreen.deactivate();
			}
	}
}

void ScreenManager::Help2() {
	int mouseX, mouseY;

	Screen help2Screen("Resources/images/help2.png");
	draw(help2Screen);

	while(help2Screen.isActive()) {
		SDL_GetMouseState(&mouseX, &mouseY);
		SDL_Event myEvent;

		if(SDL_PollEvent(&myEvent) && myEvent.type == SDL_MOUSEBUTTONDOWN)
			if(mouseX > 605 && mouseX < 770 && mouseY > 540 && mouseY < 625) {
				help2Screen.deactivate();
			}
	}
}

void ScreenManager::Backstory() {
	int mouseX, mouseY;

	Screen storyScreen("Resources/images/story.png");
	draw(storyScreen);

	while(storyScreen.isActive()) {
		SDL_GetMouseState(&mouseX, &mouseY);
		SDL_Event myEvent;

		if(SDL_PollEvent(&myEvent) && myEvent.type == SDL_MOUSEBUTTONDOWN)
			if(mouseX > 594 && mouseX < 772 && mouseY > 528 && mouseY < 610)
				storyScreen.deactivate();
	}
}

void ScreenManager::Credits() {
	int mouseX, mouseY;

	Screen creditsScreen("Resources/images/credits.png");
	draw(creditsScreen);

	while(creditsScreen.isActive()) {
		SDL_GetMouseState(&mouseX, &mouseY);
		SDL_Event myEvent;

		if(SDL_PollEvent(&myEvent) && myEvent.type == SDL_MOUSEBUTTONDOWN)
			if(mouseX > 587 && mouseX < 775 && mouseY > 475 && mouseY < 567)
				creditsScreen.deactivate();
	}
}

void ScreenManager::LevelChange() {
	Uint32 timer = SDL_GetTicks();
	Mix_PauseMusic();

	Screen lvlChgScreen("Resources/images/lvlChg.png");
	draw(lvlChgScreen);

	while(lvlChgScreen.isActive()) {
		if(SDL_GetTicks() - timer > 3000)
			lvlChgScreen.deactivate();
	}
	Mix_ResumeMusic();
}

bool ScreenManager::Pause() {
	bool end = false;
	int mouseX, mouseY;

	Mix_PauseMusic();

	Screen pauseScreen("Resources/images/pause.png");
	draw(pauseScreen);

	while(pauseScreen.isActive()) {
		SDL_GetMouseState(&mouseX, &mouseY);
		SDL_Event myEvent;

		if(SDL_PollEvent(&myEvent) && myEvent.type == SDL_MOUSEBUTTONDOWN)
			if(mouseY > 295 && mouseY < 471) {
				//If the user chooses "Resume"
				if(mouseX < 255 && mouseX > 145) {
					pauseScreen.deactivate();
				}

				//If the player chooses "Exit"
				if(mouseX < 684 && mouseX > 634) {
					end = true;
					pauseScreen.deactivate();
				}

				if(mouseX < 621 && mouseX > 571) {
					ScreenManager::Credits();
					draw(pauseScreen);
				}

				if(mouseX < 539 && mouseX > 429) {
					ScreenManager::Help1();
					draw(pauseScreen);
				}

				if(mouseX < 396 && mouseX > 286) {
					ScreenManager::Backstory();
					draw(pauseScreen);
				}
			}
	}

	Mix_ResumeMusic();

	return end;
}

bool ScreenManager::EndDeath() {
	bool playAgain = false;
	int mouseX, mouseY;

	Screen deathScreen("Resources/images/deathEnd.png");
	draw(deathScreen);

	while(deathScreen.isActive()) {
		SDL_GetMouseState(&mouseX, &mouseY);
		SDL_Event myEvent;

		if(SDL_PollEvent(&myEvent) && myEvent.type == SDL_MOUSEBUTTONDOWN) {
			if(mouseX > 58 && mouseX < 92) {
				if(mouseY > 426 && mouseY < 465) {
					deathScreen.deactivate();
					playAgain = true;
				}
			
				if(mouseY > 469 && mouseY < 508) {
					deathScreen.deactivate();
					playAgain = false;
				}
			}
		}
	}

	return playAgain;
}

bool ScreenManager::EndSuccess() {
	bool playAgain = false;
	int mouseX, mouseY;

	Screen successScreen("Resources/images/successEnd.png");
	draw(successScreen);

	while(successScreen.isActive()) {
		SDL_GetMouseState(&mouseX, &mouseY);
		SDL_Event myEvent;

		if(SDL_PollEvent(&myEvent) && myEvent.type == SDL_MOUSEBUTTONDOWN)
			if(mouseY > 295 && mouseY < 471) {
				//If the user chooses "Play"
				if(mouseX < 255 && mouseX > 145) {
					playAgain = true;
					successScreen.deactivate();
				}

				//If the player chooses "Exit"
				if(mouseX < 684 && mouseX > 634) {
					playAgain = false;
					successScreen.deactivate();
				}

				if(mouseX < 621 && mouseX > 571) {
					ScreenManager::Credits();
					draw(successScreen);
				}

				if(mouseX < 539 && mouseX > 429) {
					ScreenManager::Help1();
					draw(successScreen);
				}

				if(mouseX < 396 && mouseX > 286) {
					ScreenManager::Backstory();
					draw(successScreen);
				}
			}			
	}

	return playAgain;
}

void ScreenManager::draw(Screen& toDraw) {
	ImageManager::draw(toDraw, SDL_GetVideoSurface(), 0, 0);
	SDL_Flip(SDL_GetVideoSurface());
}