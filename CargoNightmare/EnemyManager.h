/*
	Enemy Manager, deals with spawning, moving, attacking, and all the things that enemies do
	as the game progresses.

	Author:		Taggart Ashby
*/

#ifndef _ENEMY_MANAGER_
#define _ENEMY_MANAGER_

#include <string>
#include <vector>
#include <SDL.h>
#include "Character.h"
#include "Level.h"
#include "Enemies.h"
#include "Player.h"


class EnemyManager {
public:
	EnemyManager() {
		srand(SDL_GetTicks());
	}

	~EnemyManager() {}

	//Spawning
	void spawn(int);
	void despawn();
	
	//Movement
	void update(Character&);
	void drawEnemies();
	
	void updateDifficulty(int);

	//Check for collisions
	bool checkCollision(Player&);
	bool attackPlayer(Character&);

	void initialize();

private:
	//Keeps track of all enemies on screen.
	std::vector<Character*> totalEnemies;
};

#endif
