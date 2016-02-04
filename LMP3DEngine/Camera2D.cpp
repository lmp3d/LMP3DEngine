#include "Camera2D.h"

namespace LMP3DEngine {

Camera2D::Camera2D() : _position(0.0f, 0.0f),
	_cameraMatrix(1.0f),
	_orthMatrix(1.0f),
	_scale(1.0f),
	_needsMatrixUpdate(true),
	_screenWidth(500),
	_screenHeight(500)
{
}


Camera2D::~Camera2D()
{
}

void Camera2D::init(int screenWidth, int screenHeight) {
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
	_orthMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
}

void Camera2D::update() {

	if (_needsMatrixUpdate) {

		//Camera Translation
		glm::vec3 translate(-_position.x + _screenWidth / 2, -_position.y + _screenHeight / 2, 0.0f);
		_cameraMatrix = glm::translate(_orthMatrix, translate);

		//Camera Scale
		glm::vec3 scale(_scale, _scale, 0.0f);
		_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;

		_needsMatrixUpdate = false;
			
	}
}

glm::vec2 Camera2D::getScreenFromWorld(glm::vec2 screenCoords) {
	//invert y coords
	screenCoords.y = _screenHeight - screenCoords.y;
	//make it so 0 is the center
	screenCoords -= glm::vec2(_screenWidth / 2, _screenHeight / 2);
	//scale the coords
	screenCoords /= _scale;
	//Translate with the camera position
	screenCoords += _position;
	return screenCoords;
}

}