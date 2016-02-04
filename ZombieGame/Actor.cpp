#include "Actor.h"
#include <LMP3DEngine/ResourceManager.h>


Actor::Actor()
{
}


Actor::~Actor()
{
}

void Actor::collideWithLevel(const std::vector<std::string>& levelData) {

}

void Actor::draw(LMP3DEngine::SpriteBatch& _spriteBatch) {

	static int textureID = LMP3DEngine::ResourceManager::getTexture("Textures/circle.png").id;

	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 destRect;
	destRect.x = _position.x;
	destRect.y = _position.y;
	destRect.z = AGENT_WIDTH;
	destRect.w = AGENT_WIDTH;

	_spriteBatch.draw(destRect, uvRect, textureID, 0.0f, _color);
}