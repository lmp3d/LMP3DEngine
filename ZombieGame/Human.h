#pragma once

#include "Actor.h"

class Human : public Actor
{
public:
	Human();
	virtual ~Human();

	virtual void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies);
};

