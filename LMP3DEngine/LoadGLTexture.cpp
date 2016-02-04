#include "LoadGLTexture.h"
#include "Errors.h"

namespace LMP3DEngine {

	GLTexture LoadGLTexture::LoadTexture(std::string filePath) {
		GLTexture texture = {};
		int width;
		int height;
		const char* path = filePath.c_str();
		texture.id = SOIL_load_OGL_texture
			(
			path,
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y
			);
		if (0 == texture.id) {
			fatalError("SOIL Failed to load texture");
		}
		glBindTexture(GL_TEXTURE_2D, texture.id);

		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);

		texture.width = width;
		texture.height = height;
		return texture;
	}

}