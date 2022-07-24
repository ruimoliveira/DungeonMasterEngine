#pragma once

#ifndef engine_h
#define engine_h

#include <GLFW/glfw3.h>
#include <string>

#include "gameLogic.h"
#include "Game/game.h"
#include "Engine/Rendering/shader.h"

/**
 * @class Engine
 * @brief Implementation of basic game engine functionality
 */
class Engine {
public:
	Engine() {};
	~Engine();
	void run();

private:
	const std::string name {"Dungeon Master Engine"};
	GLFWwindow* window {nullptr};
	GameLogic* gameLogic {nullptr};
	bool running {false};
	Shader* shader {nullptr};

	int initGLFW();
	int initOpenGL();
	void initGameLogic();
	void mainLoop();
	void handleEvents();
	void update();
	void render();
	void clean();
};

#endif // engine_h