#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/glew.h>

#include "LMP3DEngine.h"

namespace LMP3DEngine {

	int init() {
		//Initialize SDL
		SDL_Init(SDL_INIT_EVERYTHING);

		//Tell SDL that we want a double buffered window so we don't get any flickering
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		//Start SDL_image
		int flags = IMG_INIT_PNG /**| IMG_INIT_JPG | IMG_INIT_TIF**/;
		IMG_Init(flags);

		return 0;
	}

}