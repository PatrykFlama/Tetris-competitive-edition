#include "../../VScode/UWr/MIA/template.cpp"
// mandatory libs: cstdlib, windows.h


struct Board{
    int HEIGHT, WIDTH;
    #define board_type char
    /*board variables:
      -> nothing
    | -> wall
    - -> floor/celling
    # -> set brick
    * -> falling brick
    */

    vector< vector<board_type> > board;        // [row/height][column/width]

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

    bool block_detect_colision(int x, int y){       //? parse block and check for collision; true - colision detected
        bool collision = false;
        board[x][y] = 'x'; // temporary marker for visited cells
        const int dirs[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

        FOR(4){
            if(safe(dirs[i][0], dirs[i][1])) if(board[x+dirs[i][0]][y+dirs[i][1]] == '*'){
                collision = block_detect_colision(x+dirs[i][0], y+dirs[i][1]);
            }
        }

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


int main(){
    Board board;

    board.draw_board();
}
