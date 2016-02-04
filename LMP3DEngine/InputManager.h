#pragma once

#include <unordered_map>
#include <glm/glm.hpp>

namespace LMP3DEngine {

class InputManager
{
public:
	InputManager();
	~InputManager();

	void pressKey(unsigned int keyID);
	void releaseKey(unsigned int keyID);

	void setMouseCoords(float x, float y);

	bool isKeyPressed(unsigned int keyID);

	//getters
	glm::vec2 getMouseCoords() const { return _mouseCoords; }

private:
	std::unordered_map<unsigned int, bool> _keyMap;
	glm::vec2 _mouseCoords;

};

}