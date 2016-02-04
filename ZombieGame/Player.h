#pragma once

#include "Human.h"
#include <LMP3DEngine/InputManager.h>

class Player : public Human
{
public:
	Player();
	~Player();

	void init(float speed, glm::vec2 position, LMP3DEngine::InputManager* inputManager);

	void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies);

private:
	LMP3DEngine::InputManager* _inputManager;

};

