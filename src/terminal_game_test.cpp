#include "../../VScode/UWr/MIA/template.cpp"
// mandatory libs: cstdlib, windows.h
// TODO: (in distant future) separate main file to separate ones - probably struct per file + headers + main


struct Board{
    int HEIGHT, WIDTH;
    int game_state = 0;         //? 0 -> game in progress, 1 -> game won, -1 -> game lost
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
    Board() : Board(10, 20){}

    Board(int _HEIGHT, int _WIDTH){
        HEIGHT = _HEIGHT;
        WIDTH = _WIDTH;
        board.resize(HEIGHT, vector<board_type>(WIDTH, ' '));
    }

    void draw_board(){
        // --- terminal setup ---
        system("cls");


        // --- draw ---
        FOR(WIDTH+2) cout << '-';
        nl;

        FOR(h, HEIGHT){
            cout << '|';
            FOR(w, WIDTH){
                cout << board[h][w];
            }
            cout << "|\n";
        }

        FOR(WIDTH+2) cout << '-';
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

};


struct Game{

};


int main(){
    Board board;
    Player player_1;
    // Player player_2;
    const bool game_is_on = true;

    while(game_is_on){
        while(board.game_state == 0){       // while game is beeing played
            // TODO: get input
            // TODO: make move (if possible)
            board.draw_board();

            // TODO: check for game falling tick
                // TODO: fall the blocks (if possible)
                // TODO: redraw board to prevent visual action lag
        }
        // TODO: check result and make some end_screen
    }

    
}
