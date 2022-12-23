#ifndef BLOCK_H
#define BLOCK_H

#include "enums.h"
#include <vector>

class Block
{
    BlockType type;
    unsigned int size;
    std::vector<std::vector<bool>> blockMatrix;

public:
    Block(BlockType _type);
    BlockType getType();
    std::vector<std::vector<bool>> getMatrix();
    void rotate(RotationDirection rotationDirection);
};

#endif
