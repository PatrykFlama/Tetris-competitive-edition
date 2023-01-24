#include <bits/stdc++.h>
#include "gameplay.h"
#include "game.h"
#include "player.h"
#include "time.h"

#include "ui.h"

#include <chrono>
#include <thread>

int main(int argc, char *argv[])
{
    Game game(SINGLE_PLAYER);
    UI ui;

    bool global_game_over = false;
    while(!game.checkForGameOver()){
        game.gameLoop();
        ui.drawGame(game);
        ui.printContents();
    }   

   // Gameplay gameplay(p);
   // ui.drawGameplay(gameplay);
   // ui.printContents();
    return 0;
}
