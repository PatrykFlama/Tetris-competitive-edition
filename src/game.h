#ifndef GAME_H
#define GAME_H

#include "gameplay.h"
#include "player.h"
#include <vector>

enum GameMode
{
    SINGLE_PLAYER,
    HUMAN_VS_HUMAN,
    HUMAN_VS_BOT
};

class Game
{
    GameMode gameMode;
    void runSinglePlayer();
    void runHumanVsHuman();
    void runHumanVsBot();

public:
    Game(GameMode gameMode = SINGLE_PLAYER);
    std::vector<Gameplay> gameplays;
    bool gameLoop();        // return true if ui should be updated (action happened)
    bool checkForGameOver();
};

#endif
