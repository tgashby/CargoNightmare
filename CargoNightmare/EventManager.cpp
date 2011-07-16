#include "EventManager.h"
#include "GameManager.h"

//checkEvents returns false if the user has quit the game.
bool EventManager::checkEvents(const GameManager* gMan) {
	bool running = true;
	SDL_Event myEvent;

	if(!SDL_PollEvent(&myEvent)) {
			
	} else {
		switch(myEvent.type) {
			
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			keyboardEvent(&myEvent, gMan);
			break;

		case SDL_MOUSEMOTION:
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEBUTTONDOWN:
			mouseEvent(&myEvent, gMan);
			break;
			
		case SDL_QUIT:
			running = false;
			break;

		}
	}
	
	return running;
}

void EventManager::keyboardEvent(SDL_Event* myEvent, const GameManager* gMan) {
	if(myEvent->key.keysym.sym == SDLK_w) {
		//Player player = gMan->getPlayer();
	}

}
