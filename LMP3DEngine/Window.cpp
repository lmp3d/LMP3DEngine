#include "Window.h"
#include "Errors.h"
#include <SDL/SDL_image.h>

namespace LMP3DEngine {

	Window::Window()
	{
	}


	Window::~Window()
	{
	}

	int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags) {

		Uint32 flags = SDL_WINDOW_OPENGL;

		if (currentFlags & INVISIBLE) {
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (currentFlags & FULLSCREEN) {
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (currentFlags & BORDERLESS) {
			flags |= SDL_WINDOW_BORDERLESS;
		}

		_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);
		if (_sdlWindow == nullptr){
			fatalError("SDL Window could not be created!");
		}

		//Set up out OpenGl context
		SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
		if (glContext == nullptr){
			fatalError("SDL_GL context could not be created!");
		}

		//Set up glew
		/** glewExperimental = true; //if experienceing crashes, uncomment this code **/
		GLenum error = glewInit();
		if (error != GLEW_OK){
			fatalError("Could not initilise glew!");
		}

		//check the OpenGL Version
		printf("*** OpenGL Version: %s ***\n", glGetString(GL_VERSION));

		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

		//Set VSYNC
		SDL_GL_SetSwapInterval(0);

		int _IMG_flags = IMG_INIT_PNG /*|IMG_INIT_JPG|IMG_INIT_TIF uncomment to enable jpg and tif formats */;
		int imgInitted = IMG_Init(_IMG_flags);
		if ((imgInitted&_IMG_flags) != _IMG_flags) {
			fatalError("SDL_image failed to initialise");
		}

		//enable Alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

		return 0;

	}

	void Window::swapBuffer() {
		//Swap our buffer and draw everything to the screen
		SDL_GL_SwapWindow(_sdlWindow);
	}

}