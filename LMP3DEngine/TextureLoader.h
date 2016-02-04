#pragma once

#include <SDL\SDL.h>
#include <SDL\SDL_image.h>
#include <GL\glew.h>

#include "GLTexture.h"

#include <string>

namespace LMP3DEngine {

	class TextureLoader
	{
	public:
		static GLTexture loadPNGtoTexture(std::string filePath);
	};

}