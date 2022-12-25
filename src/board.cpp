#include "board.h"
#include "block.h"

BoardPosition::BoardPosition(int _row, int _col): row(_row), col(_col) {}

void BoardPosition::move(MoveDirection direction)
{   
    row += MOVE_ROW[direction];
    col += MOVE_COL[direction];
}

Board::Board(uint _HEIGHT, uint _WIDTH): 

    HEIGHT(_HEIGHT), WIDTH(_WIDTH), 
    startingPos(BoardPosition((uint) 0, (uint) (WIDTH - 4) / 2)),  // wyznaczanie pozycji startowej w wierzzu, tak żeby macierz4x4 klocka była na środku
    board(vvBool(HEIGHT, vBool(WIDTH, false))), 
    blockType(vvBlockType(HEIGHT, vBlockType(WIDTH, (BlockType) 0))),
    block(Block((BlockType) 0)),
    Pos(startingPos.row, startingPos.col) {}

Board::Board(): Board(standardHEIGHT, standardWIDTH) {}    // typowe wartości

void Board::setNewBlock(BlockType newType)  // ustawianie nowego klocka o danym typie na pozycji startowej
{  
    block = Block(newType);
    Pos = startingPos;
}

int Board::getRowPos() const 
{
    return Pos.row;
}

int Board::getColPos() const
{
    return Pos.col;
}

Block Board::getBlock() const 
{
    return block;
}

bool Board::getCell(BoardPosition pos) const
{
    return board[pos.row][pos.col];
}

BlockType Board::getBlockType(BoardPosition pos) const 
{
    return blockType[pos.row][pos.col];
}

void Board::clear(BoardPosition pos)
{
    board[pos.row][pos.col] = false;
    blockType[pos.row][pos.col] = (BlockType) 0;
}

void Board::clear(int row)
{
    for(uint col = 0; col < WIDTH; ++col)
        clear(BoardPosition(row, col));
}

void Board::clear()
{
    for(uint row = 0; row < HEIGHT; ++row)
        clear(row);
}

bool Board::isCellFree(BoardPosition pos) const
{
    return !board[pos.row][pos.col];
}

bool Board::isRowFree(int row) const 
{
    for(uint col = 0; col < WIDTH; ++col)
        if(!isCellFree(BoardPosition(row, col)))   return false;

    return true;
}

bool Board::isRowFull(int row) const
{
    for(uint col = 0; col < WIDTH; ++col)
        if(isCellFree(BoardPosition(row, col)))   return false;

    return true;
}

bool Board::doesNotCollideWithBoard(Block newBlock, BoardPosition newPos) const  // sprawdzanie czy klocek o zadanej pozycji nie koliduje z planszą
{
    vvBool blockMatrix = newBlock.getMatrix();

    for(uint row = 0; row < blockMatrix.size(); ++row)
    {
        for(uint col = 0; col < blockMatrix[row].size(); ++col)
        {
            if(!blockMatrix[row][col])  continue;

            BoardPosition posOnBoard(newPos.row + row, newPos.col + col);

            if(posOnBoard.row < 0 || posOnBoard.row >= HEIGHT) return false;

            if(posOnBoard.col < 0 || posOnBoard.col >= WIDTH) return false;

            if(!isCellFree(posOnBoard))   return false;
        }   
    }

    return true;   // no nie koliduje z planszą
}

bool Board::canAddBlock(BlockType type) const // czy można dodać klocek na pozycję startową, jeśli nie można no to wiadomo koniec gry
{
return doesNotCollideWithBoard(Block(type), startingPos);
}

bool Board::attemptToAddeBlock(BlockType type)    // dodawanie klocka na pozycję startową (false - nie można dodać)
{
    if(canAddBlock(type))
    {
        setNewBlock(type);
        return true;
    }
    return false;
}

bool Board::canMoveBlock(MoveDirection direction) const
{
    BoardPosition newPos = Pos;
    newPos.move(direction);

    return doesNotCollideWithBoard(block, newPos);
}

bool Board::attemptToMoveBlock(MoveDirection direction)  
{
    if(canMoveBlock(direction))
    {   // ruszenie klocka na zadaną pozycję
        Pos.move(direction);
        return true;
    }
    return false;
}

bool Board::canRotateBlock(RotationDirection direction) const
{
    Block blockCopy = block;    // kopiowanie klocka, żeby można było zrobić spokojnie obrót, sprawdzić czy jeste poprawy a dopiero potem go zastosować
    blockCopy.rotate(direction);

    return doesNotCollideWithBoard(blockCopy, Pos);
}

bool Board::attemptToRotateBlock(RotationDirection direction)
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

bool Board::removeRow(int row)
{
    if(row < 0) return 0;

    clear(row);

    for(int cRow = row - 1; cRow >= 0; --cRow)  
        dropRow(cRow);

    return 1;
}

uint Board::fixBoard()  // usuwanie tych wiersz, które są pełne i spuszczanie tych pod kótrymi jest pusto
{
    uint countDeletedRows = 0;
    
    for(uint row = 0; row < HEIGHT; ++row)
        if(isRowFull(row))  countDeletedRows += removeRow(row);

    return countDeletedRows;
}

bool Board::setOnBoard()    // ustawianie klocka na planszy
{
    if(!doesNotCollideWithBoard(block, Pos))   return false;    // koliduje to naura byku

    vvBool blockMatrix = block.getMatrix();

    for(uint row = 0; row < blockMatrix.size(); row++)
    {
        for(uint col = 0; col < blockMatrix[row].size(); col++)
        {
            if(!blockMatrix[row][col])  continue;

            BoardPosition posOnBoard(Pos.row + row, Pos.col + col);

            // nowe pozycje na planszy są dobre bo klocek doesNotCollideWithBoard

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

void Board::tick()
{
    // TODO
}

int main()
{
    Board plansza;
}

