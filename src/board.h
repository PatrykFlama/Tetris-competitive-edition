#ifndef BOARD_H
#define BOARD_H

#include "block.h"

typedef unsigned int uint;

enum MoveDirection
{
    LEFT,
    DOWN,
    RIGHT,
    UP
};

extern constexpr char moveRow[4] = {0, +1, 0, -1};
extern constexpr char moveCol[4] = {-1, 0, +1, 0};    // imo nie ma sensu tego trzymać w strukturze pozycji

struct Position
{
    int row, col;

    Position();
    Position(int _row, int _col);

    void move(MoveDirection direction);

};

class Board
{
    uint HEIGHT, WIDTH;

    Position startingPos;

    std::vector<std::vector<bool>> board;
    std::vector<std::vector<BlockType>> blockType;

    Block block;

    Position Pos;

    void setNewBlock(BlockType type);

    void clear(int row);
    void clear(Position pos);

    bool isCellFree(Position pos);

    bool isRowFree(int row);
    bool isRowFull(int row);

    bool isLegal(Block newBlock, Position pos);    

    bool canAddBlock(BlockType type);
    bool canMoveBlock(MoveDirection direction);
    bool canRotateBlock(RotationDirection direction);

    void dropRow(int row);
    void removeRow(int row);

    void fixBoard();
    bool fixBlock();

    bool setOnBoard(); 

public:

    Board();
    Board(unsigned int _HEIGHT, unsigned int _WIDTH);

    void tick();    // TODO

    void clear();  

    int getRowPos();
    int getColPos();

    Block getBlock();

    bool getCell(Position pos); 
    BlockType getBlockType(Position pos);

    bool addBlock(BlockType type);
    bool moveBlock(MoveDirection direction);
    bool rotateBlock(RotationDirection direction);

};

#endif
