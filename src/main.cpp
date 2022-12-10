#include "headers.h"
#include "game.cpp"


int main(){
    Time time;
    Board board;
    Player player_1;
    // Player player_2;
    const bool game_is_on = true;
    time.framerate = 2;
    board.board[0][0] = '*';

    while(game_is_on){
        // TODO: some menu things
        // TODO: when game start option has been chosen
            // time.restart_time();
            // board.reset();
            board.draw_board();

        while(board.game_state == 0){       // while game is beeing played
            // TODO: get input
                // TODO: make move (if possible)
                // TODO: draw board after move

            if(time.should_block_fall(board.blocks_falling_speed)){
                if(!board.block_fall()) {
                    if(!board.spawn_block()){       // block spawn failed - game over

                    }
                }
                // TODO: check for game over
                // TODO: score
                board.draw_board();
            }
        }
        // TODO: check result and make some end_screen
    }
}
