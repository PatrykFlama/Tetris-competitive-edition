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
    std::srand(std::time(0));
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

/* 
TODO LIST / KNOWN ISUUES
* block can be transfered to holding cell inf times
* sometimes global buffer overflow happens (but just sometimes, so its OK) - //! when block is dropped on another block (isCellFree(actualPosition) function)
* UI could look better
* multiplayer doesn't work
* lack of story mode
*/
