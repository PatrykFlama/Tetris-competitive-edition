
#include <ncurses.h>
#include <vector>
#include <string>

#include "ui.h"
#include "board.h"
#include "block.h"

UI::UI(){
    initscr();
    noecho();
    getmaxyx(stdscr, rows, columns );
    //TODO obslozyc termnal bezkolorowy
    start_color();
    init_pair(DEFAULT_COLOR, COLOR_WHITE, COLOR_BLACK);
    init_pair(MAIN_BORDER_COLOR, COLOR_RED, COLOR_BLACK);
    init_pair(TETRIS_BORDER_COLOR, COLOR_YELLOW, COLOR_BLACK);
    curs_set(0);
}

void UI::drawBorder() {
    attron(COLOR_PAIR(MAIN_BORDER_COLOR));
    for(int i = 0 ; i < rows ; i++) {
        mvprintw(i, 0, verticalBorder);
        mvprintw(i, columns - 1, verticalBorder);
    }
    for(int i = 0 ; i < columns ; i++) {
        mvprintw(rows - 1, i, horizontalBorder);
        mvprintw(0, i, horizontalBorder);
    }
    attroff(COLOR_PAIR(MAIN_BORDER_COLOR));
    refresh();
}

void UI::display(std::vector<std::vector<std::vector<bool>>> boards, uint score, Block nextBlock){

    //ile score i next block ma byc od gornej lewej krawedzi
    int OFFSETY = 2;
    int OFFSETX = 4;

   std::vector<std::vector<bool>>blockMatrix = nextBlock.getMatrix();


    drawBorder();

    //rysowanie scora
    char scoreString[] = "Score:";

    char scoreInt[std::to_string(score).length() + 1]; 
    strcpy(scoreInt, std::to_string(score).c_str());

    mvprintw(OFFSETY, OFFSETX, scoreString);
    mvprintw(OFFSETY, OFFSETX + sizeof(scoreString), scoreInt);


    //rysowanie next block ramka
    mvprintw(OFFSETY + 2, OFFSETX, "Next:");
    attron(COLOR_PAIR(1));
    mvprintw(OFFSETY + 3, OFFSETX, "==========");
    for(int i = 0 ; i < 4 ; i++) {
        mvprintw(OFFSETY + 4 + i, OFFSETX, "I        I");
    }
    mvprintw(OFFSETY + 8, OFFSETX, "==========");
    attroff(COLOR_PAIR(1));

    //rysowanie next block zawartosc (czyli kloc)
    attron( A_REVERSE );
    for(int i = 0 ; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(blockMatrix[i][j]) {
                mvprintw(OFFSETY + 4 +i, (OFFSETX + 1) +2*j, "  ");
            }
        }
    }
    attroff( A_REVERSE );

    //rysowanie planszy 
    //TODO 2 boardsy
    int boardWidth = boards[0][0].size();
    int boardHeight = boards[0].size();
    int boardStartX = ((columns/2) - (boardWidth));
    int boardStartY = rows - boardHeight - 2;

    //ramka
    attron(COLOR_PAIR(2));
    for(int i = -1 ; i < boardHeight+1 ; i++) {
        mvprintw(boardStartY + i, boardStartX - 1, "I");
        mvprintw(boardStartY + i, boardStartX + boardWidth*2 + 1, "I");
    }
    for(int i = -1 ; i < (boardWidth*2)+2 ; i++) {
        mvprintw(boardStartY - 1, boardStartX + i, "=");
        mvprintw(boardStartY + boardHeight, boardStartX + i, "=");
    }
    
    attroff(COLOR_PAIR(2));


    //zawartosc planszy 
    attron( A_REVERSE );

    for(int i = 0 ; i < boardHeight; i++){
        for(int j = 0; j < boardWidth; j++){
            if(boards[0][i][j]) {
                mvprintw(boardStartY + i, boardStartX + 2*j, "  ");
            }
        }
    }
    
    attroff( A_REVERSE );
    refresh();
}