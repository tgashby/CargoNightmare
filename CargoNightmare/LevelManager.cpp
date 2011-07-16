#include "LevelManager.h"

//Progress one level
void LevelManager::changeLvl() {
	if(this->getLvl().getDifficulty() < 5) {
		std::stringstream lvlStream;

		lvlStream << "Resources/levels/room_" << this->getLvl().getDifficulty()
			<< ".png";
	
		//Update the current level and current difficulty
		Level newLvl(lvlStream.str().c_str(), this->getLvl().getDifficulty() + 1);

		this->setLvl(newLvl);
	}
}

void LevelManager::initialize() {
	Level firstLvl("Resources/levels/room_0.png", 1);

	this->setLvl(firstLvl);
}