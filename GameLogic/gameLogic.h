#pragma once

#ifndef gameLogic_h
#define gameLogic_h

#include "Game/game.h"

class GameLogic {
public:
	GameLogic() {};
	~GameLogic() {};

	void update();

private:
	int gameState {};
	Game* game {nullptr};

};

#endif
