#include "../../VScode/UWr/MIA/template.cpp"
// mandatory libs: cstdlib, windows.h
// TODO: (in distant future) separate main file to separate ones - probably struct per file + headers + main

struct Time{
    int framerate;      // !frames per second
    int time_start;
    int last_block_movement;    // this probably should be in game structure, but at this point in time it is nonexistent
    int last_frame;
    const int M = 1e7;

    Time() : Time(30, 1000){}
    Time(int _framerate, int game_start_delay) : framerate(_framerate), time_start(time()){
        last_block_movement = time() + game_start_delay;
        last_frame = 0;
    }

    int time() {
        return (chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count()) % M;
    }

    int ticks(){
        return ((time()-time_start)*framerate)/1000;
    }

    int restart_time(){
        time_start = time();
    }

    bool next_frame(){
        if(last_frame < ticks()){
            last_frame = ticks();
            return true;
        }
        return false;
    }

    bool should_block_fall(int blocks_falling_speed){    // this probably should be in game structure, but at this point in time it is nonexistent
        if(blocks_falling_speed < time() - last_block_movement){
            last_block_movement += blocks_falling_speed;
            return true;
        }
        return false;
    }
};


struct Board{
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

    vector< vector<board_type> > board;        //? [row/height][column/width]; enumerated from 0

    // __init__
    Board() : Board(10, 20, 1000){}

    Board(int _HEIGHT, int _WIDTH, int _blocks_falling_speed){
        HEIGHT = _HEIGHT;
        WIDTH = _WIDTH;
        board.resize(HEIGHT, vector<board_type>(WIDTH, ' '));

        game_state = 0;
        blocks_falling_speed = _blocks_falling_speed;
    }

    void draw_board(){
        // --- terminal setup ---
        system("cls");

        // --- draw ---
        FOR(WIDTH+2) putchar('-');
        nl;

        FOR(h, HEIGHT){
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

    bool block_detect_colision(int x, int y, bool collision = false){       //? parse block and check for collision; true - colision detected
        // --- detect colision ---
        if(x == HEIGHT-1) collision = true;     // if floor hit
        else if(board[x+1][y] == '#') collision = true;   // if collided with different block

        // --- dfs ---
        board[x][y] = 'x'; // temporary marker for visited cells
        const int dirs[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

        FOR(4){
            if(safe(dirs[i][0], dirs[i][1])) if(board[x+dirs[i][0]][y+dirs[i][1]] == '*'){
                collision = block_detect_colision(x+dirs[i][0], y+dirs[i][1], collision);
            }
        }

        // --- execute results ---
        if(collision){
            board[x][y] = '#';
            return true;
        }
        board[x][y] = '*';
        return false;
    }

    void block_fall(){
        FOR(h, HEIGHT){
            FOR(w, WIDTH){
                if(board[h][w] == '*') block_detect_colision(h, w);
                if(board[h][w] == '*') board[h][w] = ' ', board[h+1][w] = '*';
            }
        }
    }
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
    time.framerate = 3;

    while(game_is_on){
        // TODO: some menu things
        // TODO: when game start option has been chosen
            time.restart_time();

        while(board.game_state == 0){       // while game is beeing played
            // TODO: get input
            // TODO: make move (if possible)
            // board.draw_board();

            if(time.should_block_fall(board.blocks_falling_speed)){
                cout << "MOVE\n";
                board.block_fall();
                // TODO: check for game over
                // TODO: score
                board.draw_board();
            }

            while(time.next_frame()){}      // wait for next frame TODO: catch user input
        }
        // TODO: check result and make some end_screen
    }
}
