#pragma once

#include <glm/glm.hpp>
#include <LMP3DEngine/SpriteBatch.h>


const float ACTOR_WIDTH = 60.0f;

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
	void checkTilePosition(const std::vector<std::string>& levelData, std::vector<glm::vec2>& collideTilePositions, float x, float y);

	void collideWithTile(glm::vec2 tilePositon);

	glm::vec2 _position;
	LMP3DEngine::Color _color;
	float _speed;
	
};

