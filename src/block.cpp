#include "block.h"
#include <vector>

std::vector<std::vector<std::vector<bool>>> blockMatrices =
    {
        {// I
         {0, 0, 1, 0},
         {0, 0, 1, 0},
         {0, 0, 1, 0},
         {0, 0, 1, 0}},
        {// J
         {1, 0, 0, 0},
         {1, 1, 1, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {// L
         {0, 0, 1, 0},
         {1, 1, 1, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {// O
         {1, 1, 0, 0},
         {1, 1, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {// S
         {0, 1, 1, 0},
         {1, 1, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {// Z
         {1, 1, 0, 0},
         {0, 1, 1, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {// T
         {0, 1, 0, 0},
         {1, 1, 1, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}}

};

unsigned int blockSizes[7] = {4, 3, 3, 2, 3, 3, 3};

Block::Block(BlockType _type = I) : type(_type), size(blockSizes[type]), blockMatrix(blockMatrices[type]) {}

BlockType Block::getType() { return type; }
std::vector<std::vector<bool>> Block::getMatrix() { return blockMatrix; }

void Block::rotate(RotationDirection rotationDirection = RIGHT)
{
    std::vector<std::vector<bool>> newMatrix = blockMatrix;

    for (unsigned int x = 0; x < size; ++x)
        for (unsigned int y = 0; y < size; ++y)
        {
            if (rotationDirection == LEFT)
                newMatrix[size - y - 1][x] = blockMatrix[x][y];
            else
                newMatrix[y][size - x - 1] = blockMatrix[x][y];
        }

    blockMatrix = newMatrix;
}
