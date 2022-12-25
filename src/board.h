#ifndef BOARD_H
#define BOARD_H

#include "block.h"

typedef unsigned int uint;

typedef std::vector<bool> vBool;
typedef std::vector<vBool> vvBool;

typedef std::vector<BlockType> vBlockType;
typedef std::vector<vBlockType> vvBlockType;

enum MoveDirection
{
    LEFT,
    DOWN,
    RIGHT,
    UP
};

extern const char MOVE_ROW[4] = {0, +1, 0, -1};
extern const char MOVE_COL[4] = {-1, 0, +1, 0};    

struct BoardPosition
{
    int row, col;

    BoardPosition();
    BoardPosition(int _row, int _col);

    void move(MoveDirection direction);

};

class Board
{
    const uint HEIGHT {20}, WIDTH {10};

    BoardPosition startingPos;

    vvBool board;
    vvBlockType blockType;

    Block block;

    BoardPosition Pos;

    void setNewBlock(BlockType type);

    void clear(int row);
    void clear(BoardPosition pos);

    bool isCellFree(BoardPosition pos);

    bool isRowFree(int row);
    bool isRowFull(int row);

    bool doesNotCollideWithBoard(Block newBlock, BoardPosition pos);    

    bool canAddBlock(BlockType type);
    bool canMoveBlock(MoveDirection direction);
    bool canRotateBlock(RotationDirection direction);

    void dropRow(int row);
    bool removeRow(int row);

    uint fixBoard();
    bool fixBlock();

    bool setOnBoard(); 

public:

    Board();
    Board(uint _HEIGHT, uint _WIDTH);

    void tick();    // TODO

    void clear();  

    int getRowPos();
    int getColPos();

    Block getBlock();

    bool getCell(BoardPosition pos); 
    BlockType getBlockType(BoardPosition pos);

    bool attemptToAddeBlock(BlockType type);
    bool attemptToMoveBlock(MoveDirection direction);
    bool attemptToRotateBlock(RotationDirection direction);

};

#endif
