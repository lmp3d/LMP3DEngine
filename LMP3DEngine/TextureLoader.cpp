#include "TextureLoader.h"
#include "Errors.h"

namespace LMP3DEngine {

	GLTexture TextureLoader::loadPNGtoTexture(std::string filePath) {
		const char* path = filePath.c_str();
		SDL_Surface *image = IMG_Load(path);
		if (image = NULL){
			fatalError("Image failed to load to SDL Surface");
		}
		SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_RGBA8888, 0);
		GLTexture texture = {};
		glGenTextures(1, &(texture.id));
		glBindTexture(GL_TEXTURE_2D, texture.id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);

		image->w = texture.width;
		image->h = texture.height;

		SDL_FreeSurface(image);

		glBindTexture(GL_TEXTURE_2D, 0);

		delete[] path;

		return texture;
	}

}
