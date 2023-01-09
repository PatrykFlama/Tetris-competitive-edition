#ifndef GAME
#define GAME

#include "gameplay.h"
#include "player.h"
#include "time.h"
#include <vector>

enum GameMode
{
    SinglePlayer,
    HumanVsHuman,
    HumanVsBot
};

class Game{
    GameMode gameMode;
    std::vector<Gameplay> gameplays;
    std::vector<Player> players;
    void runSinglePlayer();
    void runHumanVsHuman();
    void runHumanVsBot();

    public:
    Game();
    Game(GameMode gameMode);
    bool gameLoop();        // runs in main while loop
};

#endif