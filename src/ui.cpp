#include "ui.h"

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
    keypad(stdscr, TRUE);
    timeout(100);
    cbreak();
    noecho();
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
    mvprintw(position.x, position.y, "%s", str.c_str());
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
        mvprintw(x, pos1.y, "%s", verticalBorderString);
        mvprintw(x, pos2.y - 1, "%s", verticalBorderString);
    }
    for (unsigned int y = pos1.y; y < pos2.y; ++y)
    {
        mvprintw(pos1.x, y, "%s", horizontalBorderString);
        mvprintw(pos2.x - 1, y, "%s", horizontalBorderString);
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
    clear();

    drawScreenBorder();
    drawString("Score: " + std::to_string(gameplay.getScore()), position);

    // --- draw next block ---
    drawString("Next:", {position.x + 2, position.y});
    attron(COLOR_PAIR(1));
    drawBorder({position.x + 3, position.y}, {position.x + 3 + 6, position.y + 6});
    attroff(COLOR_PAIR(1));

    attron(A_REVERSE);
    drawBlock(Block(gameplay.getNextBlockType()), {position.x + 4, position.y + 1});
    attroff(A_REVERSE);

    // --- draw holding cell ---
    drawString("Hold:", {position.x + 2, position.y + 7});
    attron(COLOR_PAIR(1));
    drawBorder({position.x + 3, position.y + 7}, {position.x + 3 + 6, position.y + 7 + 6});
    attroff(COLOR_PAIR(1));

    attron(A_REVERSE);
    drawBlock(Block(gameplay.getHoldingCellBlockType()), {position.x + 4, position.y + 1 + 7});
    attroff(A_REVERSE);



    // --- draw active block ---
    drawBlock(gameplay.getBoard().activeBlock, ScreenPosition({gameplay.getBoard().activeBlockPosition.row+position.y+9, gameplay.getBoard().activeBlockPosition.col+position.x+3}));

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

void UI::drawGame(Game &game) {
    for (int i = 0; i < game.gameplays.size(); i ++){
        drawGameplay(game.gameplays[i], {2, 4+i*30});
    }
    printContents();
}
