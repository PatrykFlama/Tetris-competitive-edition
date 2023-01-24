#include "ui.h"

#include <ncurses.h>
#include <vector>
#include <string>
#include <cstring>

UI::UI()
{
    initscr();
    noecho();
    getmaxyx(stdscr, rows, columns);
    start_color();
    init_pair(DEFAULT_COLOR, COLOR_WHITE, COLOR_BLACK);
    init_pair(MAIN_BORDER_COLOR, COLOR_RED, COLOR_BLACK);
    init_pair(TETRIS_BORDER_COLOR, COLOR_YELLOW, COLOR_BLACK);
    curs_set(0);
}

UI::~UI()
{
    endwin();
}

void UI::printContents() const
{
    refresh();
}

void UI::drawString(std::string str, ScreenPosition position) const
{
    mvprintw(position.x, position.y, str.c_str());
}

void UI::drawBlock(const Block &block, ScreenPosition position) const
{
    auto matrix = block.getMatrix();
    for (int x = 0; x < matrix.size(); ++x)
        for (int y = 0; y < matrix[x].size(); ++y)
            if (matrix[x][y])
                mvprintw(position.x + x, position.y + y, "#");
}

void UI::drawBorder(ScreenPosition pos1, ScreenPosition pos2) const
{
    char verticalBorderString[2] = {VERTICAL_BORDER_CHAR, '\0'};
    char horizontalBorderString[2] = {VERTICAL_BORDER_CHAR, '\0'};

    for (unsigned int x = pos1.x; x < pos2.x; ++x)
    {
        mvprintw(x, pos1.y, verticalBorderString);
        mvprintw(x, pos2.y - 1, verticalBorderString);
    }
    for (unsigned int y = pos1.y; y < pos2.y; ++y)
    {
        mvprintw(pos1.x, y, horizontalBorderString);
        mvprintw(pos2.x - 1, y, horizontalBorderString);
    }
}

void UI::drawScreenBorder() const
{
    attron(COLOR_PAIR(MAIN_BORDER_COLOR));
    drawBorder({0, 0}, {(int)rows, (int)columns});
    attroff(COLOR_PAIR(MAIN_BORDER_COLOR));
}

void UI::drawGameplay(const Gameplay &gameplay, ScreenPosition position) const
{

    drawScreenBorder();
    drawString("Score: " + std::to_string(gameplay.getScore()), position);

    drawString("Next:", {position.x + 2, position.y});
    attron(COLOR_PAIR(1));
    drawBorder({position.x + 3, position.y}, {position.x + 3 + 6, position.y + 6});
    attroff(COLOR_PAIR(1));

    attron(A_REVERSE);
    drawBlock(Block(gameplay.getNextBlockType()), {position.x + 4, position.y + 1});
    attroff(A_REVERSE);

    ScreenPosition boardPosition = {position.x + 10, position.y};
    int boardHeight = gameplay.getBoard().getHeight();
    int boardWidth = gameplay.getBoard().getWidth();

    attron(COLOR_PAIR(2));
    drawBorder(boardPosition, {boardPosition.x + boardHeight + 2, boardPosition.y + boardWidth + 2});
    attroff(COLOR_PAIR(2));

    attron(A_REVERSE);
    for (int x = 0; x < boardHeight; x++)
    {
        for (int y = 0; y < boardWidth; y++)
        {
            if (gameplay.getBoard().isCellFull({x, y}))
            {
                mvprintw(boardPosition.x + 1 + x, boardPosition.y + 1 + y, "#");
            }
        }
    }
    attroff(A_REVERSE);
}