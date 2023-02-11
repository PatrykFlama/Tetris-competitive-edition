#include "game.h"

Game::Game(GameMode _gameMode) : gameMode(_gameMode)
{
    switch (gameMode)
    {
    case SINGLE_PLAYER:
        gameplays.emplace_back(Player(HUMAN1));
        break;
    case HUMAN_VS_HUMAN:
        gameplays.emplace_back(Player(HUMAN1));
        gameplays.emplace_back(Player(HUMAN2));
        break;
    case HUMAN_VS_BOT:
        gameplays.emplace_back(Player(HUMAN1));
        gameplays.emplace_back(Player(BOT));
        break;
    }
}

bool Game::gameLoop()
{
    bool ui_updated = false;
    for (unsigned int i = 0; i < gameplays.size(); i++){
        ui_updated = ui_updated || gameplays[i].gameLoop();
    }
    return ui_updated;
}

bool Game::checkForGameOver(){
    for (unsigned int i = 0; i < gameplays.size(); i++){
        if(gameplays[i].getGameOver()) return true;
    }
    return false;
}
