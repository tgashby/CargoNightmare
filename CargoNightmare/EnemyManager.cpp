#include "EnemyManager.h"

typedef std::vector<Character*, std::allocator<Character*>>::size_type sz_type;
typedef std::vector<Character*>::iterator itr;

void EnemyManager::spawn(int currentLvl) {
	//Randomly select one of the three enemy types
	int whichEnemy = (int)rand() % 3;

	//Set the enemies X pos to be one of the doors
	int xPos = (int)rand() % 2 * 735;
	if(xPos == 0) xPos = 47;

	//Set the enemies Y pos to be within the height of a door
	int yPos = (int)rand() % 264 + 235;

	//Allocate and place an enemy on the screen
	switch(whichEnemy) {
	case 0:
		{
			PenEnemy* pEnemy = new PenEnemy("Resources/enemies/pen.png", currentLvl, xPos, yPos);
			ImageManager::makeTransparent(pEnemy->getImage());
			ImageManager::draw(pEnemy->getImage(), SDL_GetVideoSurface(), pEnemy->getX(), pEnemy->getY());
			totalEnemies.push_back(pEnemy);
		}
		break;

	case 1:
		{
			SandwichEnemy* sEnemy = new SandwichEnemy("Resources/enemies/sandwich.png", currentLvl, xPos, yPos);
			ImageManager::makeTransparent(sEnemy->getImage());
			ImageManager::draw(sEnemy->getImage(), SDL_GetVideoSurface(), sEnemy->getX(), sEnemy->getY());
			totalEnemies.push_back(sEnemy);
		}
		break;

	case 2:
		{
			BottleEnemy* bEnemy = new BottleEnemy("Resources/enemies/bottle.png", 
				currentLvl, xPos, yPos);
			ImageManager::makeTransparent(bEnemy->getImage());
			ImageManager::draw(bEnemy->getImage(), SDL_GetVideoSurface(), bEnemy->getX(), bEnemy->getY());
			totalEnemies.push_back(bEnemy);
		}
		break;
	}
}

//Despawn all enemies
void EnemyManager::despawn() {
	for(unsigned int i = 0; i < totalEnemies.size(); i++) {
		delete totalEnemies.at(i);
		totalEnemies.erase(totalEnemies.begin() + i);
	}
}

void EnemyManager::update(Character& player) {
	for(sz_type i = 0; i < totalEnemies.size(); i++)
		totalEnemies.at(i)->move(player);
}

void EnemyManager::drawEnemies() {
	for(sz_type i = 0; i < totalEnemies.size(); i++) {
		Character* currEnemy = totalEnemies.at(i);

		ImageManager::draw(currEnemy->getImage(), SDL_GetVideoSurface(),
			currEnemy->getX(), currEnemy->getY());
	}
}

bool EnemyManager::checkCollision(Player& player) {
	unsigned int i;
	int mouseX, mouseY;
	Character* currEnemy;
	bool collision = false;

	//Get the mouse position
	SDL_GetMouseState(&mouseX, &mouseY);
	
	for(i = 0; i < totalEnemies.size(); i++) {
		currEnemy = totalEnemies.at(i);

		//Check if the mouse coordinates are within an enemy image
		if(mouseX < (currEnemy->getX() + (int)currEnemy->getWidth()) && 
			mouseX > currEnemy->getX() &&
			mouseY < ((int)currEnemy->getHeight() + currEnemy->getY()) && 
			mouseY > currEnemy->getY()) {
			collision = true;
			break;
		}
	}

	if(collision) {
		currEnemy->setHealth(currEnemy->getHealth() - 
			player.getWeap().getPower());

		if(currEnemy->getHealth() <= 0) {
			delete currEnemy;
			totalEnemies.erase(totalEnemies.begin() + i);
		}
	}

	return collision;
}

bool EnemyManager::attackPlayer(Character& player) {
	Character* currEnemy;
	std::vector<Character*> attackers;
	bool collision = true;

	for(unsigned int i = 0; i < totalEnemies.size(); i++) {
		currEnemy = totalEnemies.at(i);

		//If the player's right side is less than the enemy's left side,
		//no collision is possible
		if(player.getX() + (int)player.getWidth() < currEnemy->getX()) {
			collision = false;
			continue;
		}

		//If the player's left side is greater than the enemy's right side,
		//no collision is possible
		if(player.getX() > currEnemy->getX() + (int)currEnemy->getWidth()) {
			collision = false;
			continue;
		}

		//If the player's lower side is higher than the enemy's upper side,
		//no collision is possible
		if(player.getY() + (int)player.getHeight() < currEnemy->getY()) {
			collision = false;
			continue;
		}

		//If the player's upper side is lower than the enemy's lower side,
		//no collision is possible
		if(player.getY() > currEnemy->getY() + (int)currEnemy->getHeight()) {
			collision = false;
			continue;
		}
		
		//Otherwise there is a collision
		attackers.push_back(currEnemy);
	}

	for(unsigned int i = 0; i < attackers.size(); i++)
		attackers.at(i)->attack(player);

	return collision;
}

void EnemyManager::initialize() {
	this->despawn();

	totalEnemies.clear();
}