#pragma once

#ifndef game_h
#define game_h

#include <string>

/**
 * @class Game
 * @brief Implementation of game specific functionality
 */
class Game {
public:
	Game(std::string name) : name(name) {};
	~Game() {};

private:
	std::string name;
};

#endif
