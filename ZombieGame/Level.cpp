#include "Level.h"

#include <LMP3DEngine/Errors.h>
#include <fstream>
#include <iostream>
#include <LMP3DEngine/ResourceManager.h>

Level::Level(const std::string& fileName)
{
	std::ifstream file;
	file.open(fileName);

	//error checking
	if (file.fail()) {
		LMP3DEngine::fatalError("failed to open " + fileName);
	}

	//throw away first string
	std::string tmp;
	file >> tmp >> _numHumans;

	while (std::getline(file, tmp)) {
		_levelData.push_back(tmp);
	}

	_spriteBatch.init();
	_spriteBatch.begin();

	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	LMP3DEngine::Color whiteColor;
	whiteColor.r = 255;
	whiteColor.g = 255;
	whiteColor.b = 255;
	whiteColor.a = 255;

	for (int y = 0; y < _levelData.size(); y++) {
		for (int x = 0; x < _levelData[y].size(); x++) {
			// Grab the tile
			char tile = _levelData[y][x];

			//get destination rectangle
			glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

			//process the tile
			switch (tile) {
			case 'B':
			case 'R':
				_spriteBatch.draw(
					destRect,
					uvRect,
					LMP3DEngine::ResourceManager::getTexture("../ZombieGame/Textures/red_bricks.png").id,
					0.0f,
					whiteColor);
				break;
			case 'G':
				_spriteBatch.draw(
					destRect,
					uvRect,
					LMP3DEngine::ResourceManager::getTexture("../ZombieGame/Textures/glass.png").id,
					0.0f,
					whiteColor);
				break;
			case 'L':
				_spriteBatch.draw(
					destRect,
					uvRect,
					LMP3DEngine::ResourceManager::getTexture("../ZombieGame/Textures/light_bricks.png").id,
					0.0f,
					whiteColor);
				break;
			case '@' :
				_startPlayerPos.x = x * TILE_WIDTH;
				_startPlayerPos.y = y * TILE_WIDTH;
				break;
			case 'Z':
				_zombieStartPositions.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);
				break;
			case '.':
				break;
			default:
				std::printf("Unexpected Symbol %c at (%d,%d)", tile, x, y);
				break;
			}
		}
	}
	_spriteBatch.end();

}


Level::~Level()
{
}

void Level::draw() {
	_spriteBatch.renderBatch();
}
