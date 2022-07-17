#pragma once

#ifndef game_h
#define game_h

#include <string>

/**
 *
 */
class Game {
public:
	Game(std::string name) : name(name) {};
	~Game() {};

private:
	std::string name;
};

#endif
