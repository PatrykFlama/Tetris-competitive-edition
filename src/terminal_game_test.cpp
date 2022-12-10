#include "../../VScode/UWr/MIA/template.cpp"
// mandatory libs: cstdlib, windows.h
// TODO: (in distant future) separate main file to separate ones - probably struct per file + headers + main

struct Time{
    int framerate;      // !frames per second
    int time_start;
    int last_block_movement;    // this probably should be in game structure, but at this point in time it is nonexistent
    const int M = 1e7;

    Time() : Time(30, 1000){}
    Time(int _framerate, int game_start_delay) : framerate(_framerate), time_start(time()){
        last_block_movement = time() + game_start_delay;
    }

    int time() {
        return (chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count()) % M;
    }

    // int ticks(){
    //     return ((time()-time_start)*framerate)/1000;
    // }

    // int restart_time(){
    //     time_start = time();
    // }

    bool should_block_fall(int blocks_falling_speed){    // this probably should be in game structure, but at this point in time it is nonexistent
        if(blocks_falling_speed < time() - last_block_movement){
            last_block_movement += blocks_falling_speed;
            return true;
        }
        return false;
    }
};


struct Board{
    /* #region variables */
    int HEIGHT, WIDTH;
    int game_state;         //? 0 -> game in progress, 1 -> game won, -1 -> game lost
    int blocks_falling_speed;   // in milliseconds
    #define board_type char
    /*board variables:
      -> nothing
    | -> wall
    - -> floor/celling
    # -> set brick
    * -> falling brick
    */

    vector< vector<board_type> > board;        //? [row/height][column/width]; width enumerated from 0, height from 1 (with ghost layer)

    const int blocks_diagrams = 5;     // TODO: some representation of blocks
    vector<int> blocks_queue;

    /* #endregion */

    // __init__
    Board() : Board(10, 20, 1000){}

    Board(int _HEIGHT, int _WIDTH, int _blocks_falling_speed){
        HEIGHT = _HEIGHT;
        WIDTH = _WIDTH;
        board.resize(HEIGHT+1, vector<board_type>(WIDTH, ' '));

        game_state = 0;
        blocks_falling_speed = _blocks_falling_speed;
    }

    void draw_board(){
        // --- terminal setup ---
        system("cls");

        // --- draw ---
        FOR(WIDTH+2) putchar('-');
        nl;

        FOR(h, 1, HEIGHT){
            putchar('|');
            FOR(w, WIDTH){
                putchar(board[h][w]);
            }
            putchar('|');
            nl;
        }

        FOR(WIDTH+2) putchar('-');
        nl;
    }

    bool safe(int x, int y){        //? if x, y are not outside of boudndries
        if(x < HEIGHT && x >= 0 && y < WIDTH && y >= 0) return true;
        return false;
    }

    /* #region Block Falling Department */
    bool fall_block_detect_colision(int x, int y, bool collision = false){       //? parse block and check for collision; true - colision detected
        // --- detect colision ---
        if(x >= HEIGHT-1) collision = true;     // if floor hit
        else if(board[x+1][y] == '#') collision = true;   // if collided with different block

        // --- dfs ---
        board[x][y] = 'x'; // temporary marker for visited cells
        const int dirs[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

        FOR(4){
            int next_x = x+dirs[i][0], next_y = y+dirs[i][1];
            if(safe(next_x, next_y)) if(board[next_x][next_y] == '*'){
                collision = fall_block_detect_colision(next_x, next_y, collision);
            }
        }

        // --- execute results ---
        if(collision){
            board[x][y] = '#';
            return true;
        }
        board[x][y] = ' ';
        board[x+1][y] = '*';
        return false;
    }

    bool block_fall(){      // fall blocks, return false if there are no blocks
        FOR(h, HEIGHT){
            FOR(w, WIDTH){
                if(board[h][w] == '*'){
                    fall_block_detect_colision(h, w);
                    return true;
                }
            }
        }
        return false;
    }
    /* #endregion */

    /* #region Block Spawning Management */
    void redraw_blocks(){
        // TODO: push 14 blocks randomly in queue (every type of block should be choosen exactly one)
    }

    bool spawn_block(){         // if operation succeeded
        if(blocks_queue.empty()) redraw_blocks();
        // TODO: find place id 0-th line (the ghost line) to put block, if such place doesn't exist - game over
    }
    /* #endregion */
};


struct Player{
    Player() : Player(10, 20){}

    Player(int _HEIGHT, int _WIDTH){
        
    }

    void get_input(){}

    void interpret_input(){}
};


struct Game{

};


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
