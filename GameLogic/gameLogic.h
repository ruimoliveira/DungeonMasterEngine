#pragma once

#ifndef gameLogic_h
#define gameLogic_h

#include "Game/game.h"

/**
 * @class GameLogic
 * @brief Implementation of basic game logic functionality
 */
class GameLogic {
public:
	GameLogic() {};
	~GameLogic() {};

	void update();

private:
	int gameState {};
	Game* game {nullptr};

};

#endif gameLogic_h
