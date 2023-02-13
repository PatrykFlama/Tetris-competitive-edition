#ifndef BOARD_H
#define BOARD_H

#include "block.h"
#include <array>
#include <vector>
#include <exception>
#include <bits/stdc++.h>        // in theory - temporary

enum MoveDirection
{
    LEFT,
    DOWN,
    RIGHT,
    UP
};

const unsigned int DEFAULT_BOARD_HEIGHT = 20;
const unsigned int DEFAULT_BOARD_WIDTH = 10;

const std::array<int, 4> MOVE_ROW = {0, +1, 0, -1};
const std::array<int, 4> MOVE_COL = {-1, 0, +1, 0};

struct BoardPosition
{
    int row;
    int col;

    BoardPosition(int _row = 0, int _col = 0);

    void move(MoveDirection direction);
};

class Board
{
    unsigned int HEIGHT, WIDTH;

    BoardPosition startingPosition;

    std::vector<std::vector<bool> > board;
    std::vector<std::vector<BlockType> > blockTypes;

    void resizeBoard(unsigned int newHeight, unsigned int newWidth);

    bool hasActiveBlock;

    void clearPosition(BoardPosition position);
    void clearRow(unsigned int row);

    void dropRow(unsigned int row);
    void removeRow(unsigned int row);

public:
    Board(unsigned int _HEIGHT = DEFAULT_BOARD_HEIGHT, unsigned int _WIDTH = DEFAULT_BOARD_WIDTH);
    Block activeBlock;
    BoardPosition activeBlockPosition;

    void setNewBlock(BlockType type);
    const BoardPosition &getActiveBlockPosition() const;
    const Block &getActiveBlock() const;

    unsigned int getHeight() const;
    unsigned int getWidth() const;

    const std::vector<std::vector<bool>> getBoard() const;
    const std::vector<std::vector<BlockType>> getBlockTypes() const;

    bool isPositionValid(BoardPosition position) const;
    bool attemptToSolidify();
    BlockType getBlockTypeAt(BoardPosition position) const;

    bool canMoveBlock(MoveDirection direction) const;

    bool isCellFull(BoardPosition position) const;
    bool isCellFree(BoardPosition position) const;
    bool isRowFree(unsigned int row) const;
    bool isRowFull(unsigned int row) const;

    bool canAddNewBlock(BlockType type) const;
    bool canRotateActiveBlock(RotationDirection direction) const;
    bool doesNotCollideWithBoard(Block newBlock, BoardPosition newPosition) const;

    bool attemptToAddNewBlock(BlockType type);
    bool attemptToMoveActiveBlock(MoveDirection direction);
    bool attemptToRotateActiveBlock(RotationDirection direction);

    unsigned int fixBoard();
    void clearBoard();
};

#endif
