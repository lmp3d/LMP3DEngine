#pragma once

#include <glm/glm.hpp>
#include <LMP3DEngine/SpriteBatch.h>


const float AGENT_WIDTH = 60;

class Zombie;
class Human;

class Actor
{
public:
	Actor();
	virtual ~Actor();

	virtual void update(const std::vector<std::string>& levelData, 
						std::vector<Human*>& humans, 
						std::vector<Zombie*>& zombies) = 0;

	void collideWithLevel(const std::vector<std::string>& levelData);

	void draw(LMP3DEngine::SpriteBatch& _spriteBatch);

	glm::vec2 getPosition() const { return _position; }

protected:
	glm::vec2 _position;
	LMP3DEngine::Color _color;
	float _speed;
	
};

