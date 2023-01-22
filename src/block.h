#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

const unsigned int BLOCK_TYPES_COUNT = 7;

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
    CLOCKWISE,
    COUNTERCLOCKWISE
};

class Block
{
    BlockType type;
    unsigned int size;
    std::vector<std::vector<bool>> blockMatrix;

public:
    Block(BlockType _type = I);
    BlockType getType() const;
    std::vector<std::vector<bool>> getMatrix() const;
    void rotate(RotationDirection rotationDirection);
};

#endif
