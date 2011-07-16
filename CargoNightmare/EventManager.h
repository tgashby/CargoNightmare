#ifndef _EVENT_MANAGER_
#define _EVENT_MANAGER_

#include <SDL.h>
#include "GameManager.h"

class EventManager {
public:
	EventManager() {}
	~EventManager() {}

	bool checkEvents(const GameManager*);

private:
	void keyboardEvent(SDL_Event*, const GameManager*);
	void mouseEvent(SDL_Event*, const GameManager*);
};

#endif
