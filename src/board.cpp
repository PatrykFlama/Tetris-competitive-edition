#include "board.h"
#include "block.h"

constexpr int movesROW[4] = {0, +1, 0, -1};
constexpr int movesCOL[4] = {-1, 0, +1, 0};

Board::Board(unsigned int _HIGHT = 20, unsigned int _WIDTH = 10): 
    HIGHT(_HIGHT), WIDTH(_WIDTH), 
    board(std::vector<std::vector<bool>>(HIGHT, std::vector<bool>(WIDTH, false))), 
    blocktype(std::vector<std::vector<BlockType>>(HIGHT, std::vector<BlockType>(WIDTH, (BlockType) 0))),
    block(Block((BlockType) 0)),
    _ROW((WIDTH - 4) / 2), _COL(0), 
    ROW(_ROW), COL(_COL) {}

void Board::clear(int row, int col)
{
    board[row][col] = false;
    blocktype[row][col] = (BlockType) 0;
}

void Board::clear(int row)
{
    for(int col = 0; col < WIDTH; col++)  clear(row, col);
}

void Board::clear()
{
    for(int row = 0; row < HIGHT; row++)  clear(row);
}

bool Board::isFree(int row, int col)
{
    return !board[row][col];
}

bool Board::isrowFree(int row)
{
    for(int col = 0; col < WIDTH; col++)
        if(!isFree(row, col))   return false;

    return true;
}

bool Board::isrowFull(int row)
{
    for(int col = 0; col < WIDTH; col++)
        if(isFree(row, col))   return false;

    return true;
}

bool Board::isLegal(Block newBlock, int new_row, int new_col)
{
    std::vector<std::vector<bool>> blockMatrix = newBlock.getMatrix();

    for(unsigned int row = 0; row < blockMatrix.size(); row++)
    {
        for(unsigned int col = 0; col < blockMatrix[row].size(); col++)
        {
            int new_ROW = new_row + row;
            int new_COL = new_col + col;

            if(!blockMatrix[row][col])  continue;

            if(new_ROW < 0 || new_ROW >= HIGHT) return false;

            if(new_COL < 0 || new_COL >= WIDTH) return false;

            if(!isFree(new_ROW, new_COL))   return false;
        }   
    }

    return true;
}

void Board::dropRow(int row)
{
    if(!isrowFree(row + 1)) return;

    for(int col = 0; col < WIDTH; col++)
    {
        board[row + 1][col] = board[row][col];
        blocktype[row + 1][col] = blocktype[row][col];

        clear(row, col);
    }
}

void Board::removeRow(int row)
{
    clear(row);

    for(int _row = row - 1; _row >= 0; _row--)
    {
        dropRow(_row);
    }
}

void Board::fixBoard()
{
    for(int row = 0; row < HIGHT; row++)
    {
        if(isrowFull(row))
        {
            removeRow(row);
        }
    }
}

int Board::getRow()
{
    return ROW;
}

int Board::getCol()
{
    return COL;
}

Block Board::getBlock()
{
    return block;
}

bool Board::getCell(int row, int col)
{
    return board[row][col];
}

BlockType Board::getType(int row, int col)
{
    return blocktype[row][col];
}

bool Board::canAddBlock(BlockType type)
{
    return isLegal(Block(type), _ROW, _COL);
}

bool Board::canMoveBlock(MoveDirection dir)
{
    return isLegal(block, ROW + movesROW[dir], COL + movesCOL[dir]);
}

bool Board::canRotateBlock(RotationDirection dir)
{
    Block tmp = block;
    tmp.rotate(dir);

    return isLegal(tmp, ROW, COL);
}

bool Board::addBlock(BlockType type)
{
    if(canAddBlock(type))
    {
        block = Block(type);
        ROW = _ROW, COL = _COL;
        return true;
    }
    return false;
}

bool Board::moveBlock(MoveDirection dir)
{
    if(canMoveBlock(dir))
    {
        ROW += movesROW[dir];
        COL += movesCOL[dir];
        return true;
    }
    return false;
}

bool Board::rotateBlock(RotationDirection dir)
{
    if(canRotateBlock(dir))
    {
        block.rotate(dir);
        return true;
    }
    return false;
}

bool Board::setOnBoard()
{
    if(!isLegal(block, ROW, COL))   return false;

    std::vector<std::vector<bool>> blockMatrix = block.getMatrix();

    for(unsigned int row = 0; row < blockMatrix.size(); row++)
    {
        for(unsigned int col = 0; col < blockMatrix[row].size(); col++)
        {
            if(!blockMatrix[row][col])  continue;

            int new_ROW = ROW + row;
            int new_COL = ROW + col;
    
            // isLegal, so all cords have to be good 

            board[new_ROW][new_COL] = true;
            blocktype[new_ROW][new_COL] = block.getType();
        }   
    }

    block = Block((BlockType) 0);

    ROW = _ROW, COL = _COL;

    // it is time to request for new block

    return true;
}

bool Board::fixBlock()
{
    if(canMoveBlock(MoveDirection::DOWN_MOVE))
    {
        return true;
    }
    return setOnBoard(); // if true then it is time to request new block, else go on
}
