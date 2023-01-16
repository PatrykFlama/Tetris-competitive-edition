#ifndef UI_H
#define UI_H

#include "block.h"
#include "board.h"
#include <vector>

enum ColorSet
{
    DEFAULT_COLOR,
    MAIN_BORDER_COLOR,
    TETRIS_BORDER_COLOR
};

class UI
{
    uint columns;
    uint rows;
    
    std::vector<std::vector<std::vector<bool>>> blockMatrices;
    const char verticalBorder[2] = "I";
    const char horizontalBorder[2] = "=";

public:
    UI();
    void display(std::vector<std::vector<std::vector<bool>>> boards, uint score, Block nextBlock);
    //FIXME ma byc prywatna
    void drawBorder();
};

#endif
