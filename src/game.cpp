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

void Game::gameLoop()
{
    bool global_game_over = false;
    while(!global_game_over){
        for (unsigned int i = 0; i < gameplays.size(); i++){
            gameplays[i].gameLoop();
        }
        for (unsigned int i = 0; i < gameplays.size(); i++){
            if(gameplays[i].getGameOver()) global_game_over = true;
        }
    }   
}
