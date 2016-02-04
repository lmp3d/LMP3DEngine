#pragma once

#include <SDL\SDL.h>
#include <SDL\SDL_image.h>
#include <GL\glew.h>

#include <LMP3DEngine/LMP3DEngine.h>
#include <LMP3DEngine/GLSLProgram.h>
#include <LMP3DEngine/GLTexture.h>
#include <LMP3DEngine/Sprite.h>
#include <LMP3DEngine/Window.h>
#include <LMP3DEngine/InputManager.h>
#include <LMP3DEngine/Timing.h>

#include <LMP3DEngine/SpriteBatch.h>

#include <LMP3DEngine/Camera2D.h>

#include "Bullet.h"

#include <vector>

enum class GameState{PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();



private:
	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();

	LMP3DEngine::Window _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;



	LMP3DEngine::GLSLProgram _colorProgram;
	LMP3DEngine::Camera2D _camera;

	LMP3DEngine::SpriteBatch _spriteBatch;

	LMP3DEngine::InputManager _inputManager;
	LMP3DEngine::FpsLimiter _fpsLimiter;

	std::vector<Bullet> _bullets;

	float _maxFPS;
	float _fps;

	float _time;
};

