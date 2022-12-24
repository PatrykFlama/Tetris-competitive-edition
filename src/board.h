#ifndef BOARD_H
#define BOARD_H

#include <vector>

#include "block.h"

enum MoveDirection
{
    LEFT_MOVE,
    DOWN_MOVE,
    RIGHT_MOVE,
    UP_MOVE  
};

class Board
{
    int HIGHT, WIDTH;

    int _ROW, _COL; // starting pos

    std::vector<std::vector<bool>> board;
    std::vector<std::vector<BlockType>> blocktype;

    Block block;

    int ROW, COL;   // current block pos


public:

    Board();
    Board(unsigned int _HIGHT, unsigned int _WIDTH);

    void tick();    // TODO

    void clear();  

    bool addBlock(BlockType type);
    bool moveBlock(MoveDirection dir);
    bool rotateBlock(RotationDirection dir);

    int getRow();
    int getCol();

    Block getBlock();

    bool getCell(int row, int col);

    BlockType getType(int row, int col);

    bool fixBlock();  // TODO if false then setOnBoard else continue ticks/moves etc

private:

    void clear(int row);
    void clear(int row, int col);

    bool isFree(int row, int col);

    bool isrowFree(int row);
    bool isrowFull(int row);

    bool isLegal(Block newBlock, int row, int col);    

    bool canAddBlock(BlockType type);
    bool canMoveBlock(MoveDirection dir);
    bool canRotateBlock(RotationDirection dir);

    void fixBoard();

    void dropRow(int row);
    void removeRow(int row);

    bool setOnBoard();  // TODO // if block can't move down
    // true - everything fine, false - ??? XD

};

#endif