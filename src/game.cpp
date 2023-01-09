#include "game.h"

Game::Game() : Game(SinglePlayer) {}

Game::Game(GameMode _gameMode){
    // create players
    gameMode = _gameMode;
    Player player1 = Player(Human);
    players.push_back(player1);       // TODO
    gameplays.push_back(Gameplay(player1));
    if(gameMode == HumanVsHuman) {          // HumanVsHuman
        Player player2 = Player(Human);
        players.push_back(player2);
        gameplays.push_back(Gameplay(player2));
    } else if(gameMode == HumanVsBot) {
        Player player2 = Player(Bot);
        players.push_back(player2);     // TODO
        gameplays.push_back(Gameplay(player2));
    }
}


bool Game::gameLoop(){      // runs in main while loop
    for(int i = 0; i < gameplays.size(); i++)
        gameplays[i].gameLoop();
}
