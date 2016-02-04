#pragma once

#include <LMP3DEngine/Window.h>
#include <LMP3DEngine/GLSLProgram.h>
#include <LMP3DEngine/Camera2D.h>
#include <LMP3DEngine/InputManager.h>
#include <LMP3DEngine/SpriteBatch.h>

#include "Player.h"
#include "Level.h"

enum class GameState {
	PLAY,
	EXIT
};


class MainGame
{
public:
    MainGame();
    ~MainGame();

    /// Runs the game
    void run();

private:
    /// Initializes the core systems
    void initSystems();

	/// initializes the level and sets up everything
	void initLevel();

    /// Initializes the shaders
    void initShaders();

    /// Main game loop for the program
    void gameLoop();

	/// Updates all actors
	void updateActors();

    /// Handles input processing
    void processInput();

    /// Renders the game
    void drawGame();

    /// Member Variables
    LMP3DEngine::Window _window; ///< The game window
    
    LMP3DEngine::GLSLProgram _textureProgram; ///< The shader program

    LMP3DEngine::InputManager _inputManager; ///< Handles input

    LMP3DEngine::Camera2D _camera; ///< Main Camera

	LMP3DEngine::SpriteBatch _actorSpriteBatch;

	std::vector<Level*> _levels; /// vector of all levels

	int _screenWidth, _screenHeight;

	float _fps;

	int _currentLevel;

	Player* _player;

	std::vector<Human*> _humans; ///< vector of all humans

	GameState _gameState;
};

