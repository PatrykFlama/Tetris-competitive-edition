#ifndef UI_H
#define UI_H

#include "gameplay.h"
#include "block.h"
#include "game.h"
#include <string>
#include <vector>
#include <cstring>

#ifndef _WIN32
#include <ncurses.h>
#endif

#ifdef _WIN32
#define ncurses false
#define initscr()                               //? ncruses
#define printw(...) printf(__VA_ARGS__)         //? ncruses            
#define scanw(...) scanf(__VA_ARGS__)           //? ncurses 
#define getch() getchar()                       //? ncruses       
#define refresh()                               //? ncruses
#define clear() printf("\e[1;1H\e[2J");         //? ncruses                    
#define endwin()                                //? ncruses
#define start_color()                           //? ncruses
#define init_pair(index, foreground, background)//? ncruses
#define init_color(color, R, G, B)              //? ncruses from [0, 1000]
#define attron(...)                             //? ncruses
#define attroff(...)                            //? ncruses
#define keypad(...)

#define KEY_UP 'k'
#define KEY_DOWN 'k'
#define KEY_LEFT 'k'
#define KEY_RIGHT 'k'
#define KEY_ENTER 'k'

#define noecho()
#define curs_set(...)
#define getmaxyx(...)
#define mvprintw(...)
#define timeout(...)
#define cbreak()
#endif

enum ColorSet
{
    DEFAULT_COLOR,
    MAIN_BORDER_COLOR,
    TETRIS_BORDER_COLOR
};

struct ScreenPosition
{
    int x, y;
};

class UI
{
    unsigned int columns;
    unsigned int rows;

    const static char VERTICAL_BORDER_CHAR = 'I';
    const static char HORIZONTAL_BORDER_CHAR = '=';
    void drawString(std::string str, ScreenPosition position) const;
    void drawBlock(const Block &block, ScreenPosition position) const;
    void drawBorder(ScreenPosition pos1, ScreenPosition pos2) const;
    void drawScreenBorder() const;

public:
    UI();
    ~UI();
    void printContents() const;
    void drawGameplay(const Gameplay &gameplay, ScreenPosition position = {2, 4}) const;
    void drawGame(Game &game);
};

#endif
