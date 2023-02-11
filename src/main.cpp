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

    ui.drawGame(game);
    ui.printContents();

    while(!game.checkForGameOver()){        
        if(game.gameLoop()){
            ui.drawGame(game);
        }
    }

    return 0;
}
