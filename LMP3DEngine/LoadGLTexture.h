#pragma once

#include <GL\glew.h>
#include <SOIL\SOIL.h>
#include "GLTexture.h"
#include <string>

namespace LMP3DEngine {

	class LoadGLTexture
	{
	public:
		static GLTexture LoadTexture(std::string filePath);
	};

}