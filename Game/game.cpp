#include "game.h"

#include "Engine/engine.h"
#include "GameLogic/gameLogic.h"

/**
 * @brief Creates a Game instance
 */
Game Game::gameInstance;

/**
 * @brief Instace getter
 *
 * @return Instance of the Game
 */
Game& Game::Instance() {
	return gameInstance;
}

/**
 * @brief Runs Game components
 */
void Game::Run() {
	//TODO: Load game data
    //TODO: Load User Configs;
	//TODO: Init Game Logic
	Engine::Instance().Run();
}

/**
 * @brief Updates Game components
 */
void Game::Update() {
	//TODO: Update any game stuff
	//TODO: Update GameLogic
}

/**
 * @brief Handles Game-side events
 */
void Game::HandleEvents() {
	//TODO: Let GameLogic handle events
}