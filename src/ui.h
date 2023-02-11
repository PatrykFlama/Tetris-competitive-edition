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
#include "ncurses.h"
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
