#ifndef BOARD_H
#define BOARD_H

#include "block.h"

#include <array>

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

extern const uint standardHEIGHT = 20;
extern const uint standardWIDTH = 10;

extern const std::array<char, 4> MOVE_ROW = {0, +1, 0, -1};
extern const std::array<char, 4> MOVE_COL = {-1, 0, +1, 0};    

struct BoardPosition
{
    int row, col;

    BoardPosition();
    BoardPosition(int _row, int _col);

    void move(MoveDirection direction);

};

class Board
{
    const uint HEIGHT {standardHEIGHT}, WIDTH {standardWIDTH}; // typowe wartości

    BoardPosition startingPos;

    vvBool board;
    vvBlockType blockType;

    Block block;

    BoardPosition Pos;

    void setNewBlock(BlockType type);

    void clear(int row);
    void clear(BoardPosition pos);

    bool isCellFree(BoardPosition pos) const;

    bool isRowFree(int row) const;
    bool isRowFull(int row) const;

    bool doesNotCollideWithBoard(Block newBlock, BoardPosition pos) const;    

    bool canAddBlock(BlockType type) const;
    bool canRotateBlock(RotationDirection direction) const;

    void dropRow(int row);
    bool removeRow(int row);

    bool fixBlock();

    bool setOnBoard(); 

public:

    Board();
    Board(uint _HEIGHT, uint _WIDTH);

    void tick();    // TODO

    void clear();  

    int getRowPos() const;
    int getColPos() const;

    Block getBlock() const;

    bool getCell(BoardPosition pos) const; 
    BlockType getBlockType(BoardPosition pos) const;

    bool canMoveBlock(MoveDirection direction) const;
    uint fixBoard();
    
    bool attemptToAddeBlock(BlockType type);
    bool attemptToMoveBlock(MoveDirection direction);
    bool attemptToRotateBlock(RotationDirection direction);

};

#endif
