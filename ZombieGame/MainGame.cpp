#include "MainGame.h"

#include <LMP3DEngine/LMP3DEngine.h>
#include <LMP3DEngine/Timing.h>
#include <SDL/SDL.h>
#include <iostream>

#include "Zombie.h"

MainGame::MainGame() : _screenWidth(1024), _screenHeight(768), _gameState(GameState::PLAY), _fps(0.0f), _currentLevel(0), _player(nullptr)
{
    // Empty
}

MainGame::~MainGame() {
	for (int i = 0; i < _levels.size(); i++) {
		delete _levels[i];
	}
}

void MainGame::run() {
	initSystems();

	initLevel();

	gameLoop();
}

void MainGame::initSystems() {
	LMP3DEngine::init();

	_window.create("Zombies", _screenWidth, _screenHeight, 0);
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

	initShaders();

	_actorSpriteBatch.init();

	_camera.init(_screenWidth, _screenHeight);

}

void MainGame::initLevel() {
	// Level 1
	_levels.push_back(new Level("Levels/level1.txt"));
	_currentLevel = 0;

	_player = new Player();
	_player->init(10.0f, _levels[_currentLevel]->getStartPlayerPos(), &_inputManager);

	_humans.push_back(_player);
}

void MainGame::initShaders() {
    // Compile our color shader
    _textureProgram.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
    _textureProgram.addAttribute("vertexPosition");
    _textureProgram.addAttribute("vertexColor");
    _textureProgram.addAttribute("vertexUV");
    _textureProgram.linkShaders();
}

void MainGame::gameLoop() {
   
	LMP3DEngine::FpsLimiter _fpsLimiter;
	_fpsLimiter.setMaxFPS(60.0f);

	while (_gameState == GameState::PLAY) {
		_fpsLimiter.begin();

		processInput();

		updateActors();

		_camera.setPosition(_player->getPosition());

		_camera.update();

		drawGame();

		_fps = _fpsLimiter.end();
	}
}

void MainGame::updateActors() {
	// Update all Humans
	for (int i = 0; i < _humans.size(); i++) {
		_humans[i]->update(_levels[_currentLevel]->getLevelData(), _humans, _zombies);
	}

	//Don't forget to update zombies
}

void MainGame::processInput() {
    SDL_Event evnt;
    //Will keep looping until there are no more events to process
    while (SDL_PollEvent(&evnt)) {
        switch (evnt.type) {
            case SDL_QUIT:
                // Exit the game here!
                break;
            case SDL_MOUSEMOTION:
                _inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
                break;
            case SDL_KEYDOWN:
                _inputManager.pressKey(evnt.key.keysym.sym);
                break;
            case SDL_KEYUP:
                _inputManager.releaseKey(evnt.key.keysym.sym);
                break;
            case SDL_MOUSEBUTTONDOWN:
                _inputManager.pressKey(evnt.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                _inputManager.releaseKey(evnt.button.button);
                break;
        }
    }
}

void MainGame::drawGame() {
    // Set the base depth to 1.0
    glClearDepth(1.0);
    // Clear the color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_textureProgram.use();

	//draw code goes here
	glActiveTexture(GL_TEXTURE0);

	//make sure the shader uses texture 0
	GLint textureUniform = _textureProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);

	//grab tyhe camera matrix
	glm::mat4 projectionMatrix = _camera.getCameraMatrix();
	GLint pUniform = _textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	// Draw the level
	_levels[_currentLevel]->draw();

	//Begin drawing actors;
	_actorSpriteBatch.begin();

	// Draw the humans
	for (int i = 0; i < _humans.size(); i++) {
		_humans[i]->draw(_actorSpriteBatch);
	}

	_actorSpriteBatch.end();

	_actorSpriteBatch.renderBatch();
   
	_textureProgram.unuse();

    // Swap our buffer and draw everything to the screen!
    _window.swapBuffer();
}