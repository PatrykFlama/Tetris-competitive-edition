#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

enum BlockType
{
    I,
    J,
    L,
    O,
    S,
    Z,
    T
};

enum RotationDirection
{
    LEFT,
    RIGHT
};

class Block
{
    BlockType type;
    unsigned int size;
    std::vector<std::vector<bool>> blockMatrix;

public:
    Block(BlockType _type);
    BlockType getType() const;
    std::vector<std::vector<bool>> getMatrix() const;
    void rotate(RotationDirection rotationDirection);
};

#endif
