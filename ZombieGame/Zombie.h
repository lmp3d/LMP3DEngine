#pragma once

#include "Actor.h"

class Zombie : public Actor
{
public:
	Zombie();
	~Zombie();

	virtual void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies);
};

