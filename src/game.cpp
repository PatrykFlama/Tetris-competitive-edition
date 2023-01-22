#include "game.h"

Game::Game(GameMode _gameMode) : gameMode(_gameMode)
{
    switch (gameMode)
    {
    case SINGLE_PLAYER:
        gameplays.emplace_back(Player(HUMAN));
        break;
    case HUMAN_VS_HUMAN:
        gameplays.emplace_back(Player(HUMAN));
        gameplays.emplace_back(Player(HUMAN));
        break;
    case HUMAN_VS_BOT:
        gameplays.emplace_back(Player(HUMAN));
        gameplays.emplace_back(Player(BOT));
        break;
    }
}

void Game::gameLoop()
{
    for (unsigned int i = 0; i < gameplays.size(); i++)
        gameplays[i].gameLoop();
}
