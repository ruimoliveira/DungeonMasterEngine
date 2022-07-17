#pragma once

#ifndef engine_h
#define engine_h

#include <GLFW/glfw3.h>
#include <string>

#include "gameLogic.h"
#include "Game/game.h"

/**
 * @class Engine
 * @brief Implementation of basic game engine functionality
 */
class Engine {
public:
	Engine(std::string name) : name(name) {};
	~Engine() {};
	void run();

private:
	std::string name;
	GLFWwindow* window {nullptr};
	GameLogic* gameLogic {nullptr};
	bool running {false};

	int initGLFW();
	int initGLAD();
	void initOpenGL();
	void initGameLogic();
	void mainLoop();
	void handleEvents();
	void update();
	void render();
	void clean();
};

#endif