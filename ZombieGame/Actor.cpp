#include "Actor.h"
#include <LMP3DEngine/ResourceManager.h>
#include "Level.h"
#include <algorithm>


Actor::Actor()
{
}


Actor::~Actor()
{
}

void Actor::collideWithLevel(const std::vector<std::string>& levelData) {

	std::vector<glm::vec2> collideTilePositions;

	// Check the corners
	// First corner
	checkTilePosition(levelData, collideTilePositions, _position.x, _position.y);

	// Second Corner
	checkTilePosition(levelData, collideTilePositions, _position.x + ACTOR_WIDTH, _position.y);

	// Third Corner
	checkTilePosition(levelData, collideTilePositions, _position.x, _position.y + ACTOR_WIDTH);

	// Fourth Corner
	checkTilePosition(levelData, collideTilePositions, _position.x + ACTOR_WIDTH, _position.y + ACTOR_WIDTH);

	// Do collision
	for (int i = 0; i < collideTilePositions.size(); i++) {
		collideWithTile(collideTilePositions[i]);
	}

}

void Actor::draw(LMP3DEngine::SpriteBatch& _spriteBatch) {

	static int textureID = LMP3DEngine::ResourceManager::getTexture("Textures/circle.png").id;

	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 destRect;
	destRect.x = _position.x;
	destRect.y = _position.y;
	destRect.z = ACTOR_WIDTH;
	destRect.w = ACTOR_WIDTH;

	_spriteBatch.draw(destRect, uvRect, textureID, 0.0f, _color);
}

void Actor::checkTilePosition(const std::vector<std::string>& levelData, std::vector<glm::vec2>& collideTilePositions, float x, float y) {

	glm::vec2 cornerPosition = glm::vec2(floor(x / (float)TILE_WIDTH),
											floor(y / (float)TILE_WIDTH));

	if (levelData[cornerPosition.y][cornerPosition.x] != '.') {
		collideTilePositions.push_back(cornerPosition * (float)TILE_WIDTH + glm::vec2((float)TILE_WIDTH / 2.0f));
	}

}

// Axis Aligned Bounding Box Collision
void Actor::collideWithTile(glm::vec2 tilePositon) {

	const float ACTOR_RADIUS = ACTOR_WIDTH / 2.0f;
	const float TILE_RADIUS = (float)TILE_WIDTH / 2.0f;
	const float MIN_DISTANCE = ACTOR_RADIUS + TILE_RADIUS;

	glm::vec2 centerPlayerPosition = _position + glm::vec2(ACTOR_RADIUS);
	glm::vec2 distanceVector = centerPlayerPosition - tilePositon;

	float xDepth = MIN_DISTANCE - abs(distanceVector.x);
	float yDepth = MIN_DISTANCE - abs(distanceVector.y);

	if (xDepth > 0 || yDepth > 0) {
		if (std::max(xDepth, 0.0f) < std::max(yDepth, 0.0f)) {
			if (distanceVector.x < 0) {
				_position.x -= xDepth;
			}
			else {
				_position.x += xDepth;
			}
		}
		else {
			if (distanceVector.y < 0) {
				_position.y -= yDepth;
			}
			else {
				_position.y += yDepth;
			}
		}
	}

}