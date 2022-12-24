#include "board.h"
#include "block.h"

Position::Position(int _row, int _col): row(_row), col(_col) {}

void Position::move(MoveDirection direction)
{   
    row += moveRow[direction];
    col += moveCol[direction];
}

Board::Board(uint _HEIGHT = 20, uint _WIDTH = 10): 

    HEIGHT(_HEIGHT), WIDTH(_WIDTH), 
    startingPos(Position(0, (WIDTH - 4) / 2)),  // wyznaczanie pozycji startowej w wierzu, tak żeby macierz4x4 klocka była na środku
    board(std::vector<std::vector<bool>>(HEIGHT, std::vector<bool>(WIDTH, false))), 
    blockType(std::vector<std::vector<BlockType>>(HEIGHT, std::vector<BlockType>(WIDTH, (BlockType) 0))),
    block(Block((BlockType) 0)),
    Pos(startingPos.row, startingPos.col) {}


void Board::setNewBlock(BlockType newType)  // ustawianie nowego klocka o danym typie na pozycji startowej
{  
    block = Block(newType);
    Pos = startingPos;
}

uint Board::getRowPos()
{
    return Pos.row;
}

uint Board::getColPos()
{
    return Pos.col;
}

Block Board::getBlock()
{
    return block;
}

bool Board::getCell(Position pos)
{
    return board[pos.row][pos.col];
}

BlockType Board::getBlockType(Position pos)
{
    return blockType[pos.row][pos.col];
}

void Board::clear(Position pos)
{
    board[pos.row][pos.col] = false;
    blockType[pos.row][pos.col] = (BlockType) 0;
}

void Board::clear(int row)
{
    for(uint col = 0; col < WIDTH; ++col)   clear(Position(row, col));
}

void Board::clear()
{
    for(uint row = 0; row < HEIGHT; ++row)  clear(row);
}

bool Board::isCellFree(Position pos)
{
    return !board[pos.row][pos.col];
}

bool Board::isRowFree(int row)
{
    for(uint col = 0; col < WIDTH; ++col)
        if(!isCellFree(Position(row, col)))   return false;

    return true;
}

bool Board::isRowFull(int row)
{
    for(uint col = 0; col < WIDTH; ++col)
        if(isCellFree(Position(row, col)))   return false;

    return true;
}

bool Board::isLegal(Block newBlock, Position newPos)   // sprawdzanie czy klocek o zadanej pozycji nie koliduje z planszą
{
    std::vector<std::vector<bool>> blockMatrix = newBlock.getMatrix();

    for(uint row = 0; row < blockMatrix.size(); ++row)
    {
        for(uint col = 0; col < blockMatrix[row].size(); ++col)
        {
            if(!blockMatrix[row][col])  continue;

            Position posOnBoard(newPos.row + row, newPos.col + col);

            if(posOnBoard.row < 0 || posOnBoard.row >= HEIGHT) return false;

            if(posOnBoard.col < 0 || posOnBoard.col >= WIDTH) return false;

            if(!isCellFree(posOnBoard))   return false;
        }   
    }

    return true;
}

bool Board::canAddBlock(BlockType type) // czy można dodać klocek na pozycję startową, jeśli nie można no to wiadomo koniec gry
{
    return isLegal(Block(type), startingPos);
}

bool Board::addBlock(BlockType type)    // dodawanie klocka na pozycję startową (false - nie można dodać)
{
    if(canAddBlock(type))
    {
        setNewBlock(type);
        return true;
    }
    return false;
}

bool Board::canMoveBlock(MoveDirection direction)
{
    Position newPos = Pos;
    newPos.move(direction);

    return isLegal(block, newPos);
}

bool Board::moveBlock(MoveDirection direction)  
{
    if(canMoveBlock(direction))
    {   // ruszenie klocka na zadaną pozycję
        Pos.move(direction);
        return true;
    }
    return false;
}

bool Board::canRotateBlock(RotationDirection direction)
{
    Block blockCopy = block;    // kopiowanie klocka, żeby można było zrobić spokojnie obrót, sprawdzić czy jeste poprawy a dopiero potem go zastosować
    blockCopy.rotate(direction);

    return isLegal(blockCopy, Pos);
}

bool Board::rotateBlock(RotationDirection direction)
{
    if(canRotateBlock(direction))
    {
        block.rotate(direction);
        return true;
    }
    return false;
}

void Board::dropRow(int row)    // spuszczanie wiersza niżej jeśli pod nim jest pusto
{
    if(!isRowFree(row + 1)) return;

    for(uint col = 0; col < WIDTH; ++col)
    {
        board[row + 1][col] = board[row][col];
        blockType[row + 1][col] = blockType[row][col];
    }

    clear(row);
}

void Board::removeRow(int row)
{
    clear(row);

    if(row <= 0)    return;

    for(uint cRow = row - 1; cRow >= 0; --cRow)  dropRow(cRow);
}

void Board::fixBoard()  // usuwanie tych wiersz, które są pełne i spuszczanie tych pod kótrymi jest pusto
{
    for(uint row = 0; row < HEIGHT; ++row)
        if(isRowFull(row))  removeRow(row);
}

bool Board::setOnBoard()    // ustawianie klocka na planszy
{
    if(!isLegal(block, Pos))   return false;

    std::vector<std::vector<bool>> blockMatrix = block.getMatrix();

    for(uint row = 0; row < blockMatrix.size(); row++)
    {
        for(uint col = 0; col < blockMatrix[row].size(); col++)
        {
            if(!blockMatrix[row][col])  continue;

            Position posOnBoard(Pos.row + row, Pos.col + col);

            // nowe pozycje na planszy są dobre bo klocek isLegal

            if(!isCellFree(posOnBoard))   return false;

            board[posOnBoard.row][posOnBoard.col] = true;
            blockType[posOnBoard.col][posOnBoard.row] = block.getType();
        }   
    }

    setNewBlock((BlockType) 0); // czyszczenie akutalnego klocka, true - oczekiwanie na nowego klocka

    return true;
}

bool Board::fixBlock()
{
    if(canMoveBlock(MoveDirection::DOWN))   return true;    // jeśli klock może ruszyc się w dól to można grać dalej
    return setOnBoard();    // skoro klocek nie może ruszyć się w dół to trzeba go ustawić na planszy
}

void tick()
{
    // TODO
}

