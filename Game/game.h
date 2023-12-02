#pragma once

#ifndef game_h
#define game_h

/**
 * @class Game
 * @brief Representation of a game
 */
class Game {
public:
    ~Game() = default;

    static Game& Instance();

private:
    Game() = default;

    static Game gameInstance;

public:
    void Run();
    void Update();
    void HandleEvents();

private:

};

#endif // game_h
