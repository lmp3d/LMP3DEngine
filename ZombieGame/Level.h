#pragma once

#include <string>
#include <vector>

#include <LMP3DEngine/SpriteBatch.h>

const int TILE_WIDTH = 64;

class Level
{
public:
	// Load the level
	Level(const std::string& fileName);
	~Level();

	void draw();

	// getters
	const std::vector<std::string>& getLevelData() const { return _levelData; }
	glm::vec2 getStartPlayerPos() const { return _startPlayerPos; }
	const std::vector<glm::vec2>& getZombieStartPos() const { return _zombieStartPositions; }

private:
	std::vector<std::string> _levelData;
	int _numHumans;
	LMP3DEngine::SpriteBatch _spriteBatch;

	glm::vec2 _startPlayerPos;
	std::vector<glm::vec2> _zombieStartPositions;
};

