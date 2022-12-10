#include "headers.h"

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