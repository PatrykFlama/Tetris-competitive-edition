#include "board.h"
#include "block.h"
#include "ncurses.h"
BoardPosition::BoardPosition(int _row, int _col) : row(_row), col(_col) {}

void BoardPosition::move(MoveDirection direction)
{
    row += MOVE_ROW[direction];
    col += MOVE_COL[direction];
}

Board::Board(unsigned int _HEIGHT, unsigned int _WIDTH) : HEIGHT(_HEIGHT), WIDTH(_WIDTH)
{
    resizeBoard(HEIGHT, WIDTH);
    clearBoard();
    startingPosition = BoardPosition(0, (unsigned int)(WIDTH - 4) / 2);
    hasActiveBlock = false;
}

const std::vector<std::vector<bool>> Board::getBoard() const {
    return board;
}
const std::vector<std::vector<BlockType>> Board::getBlockTypes() const {
    return blockTypes;
}

void Board::resizeBoard(unsigned int newHeight, unsigned int newWidth)
{
    board.resize(newHeight);
    blockTypes.resize(newHeight);
    for (unsigned int row = 0; row < HEIGHT; ++row)
    {
        board[row].resize(newWidth);
        blockTypes[row].resize(newWidth);
    }
}

bool Board::isPositionValid(BoardPosition position) const
{
    if (position.row < 0 || position.row >= (int)HEIGHT)
        return false;
    if (position.col < 0 || position.col >= (int)WIDTH)
        return false;
    return true;
}

void Board::setNewBlock(BlockType newType)
{
    activeBlock = Block(newType);
    activeBlockPosition = startingPosition;
    hasActiveBlock = true;
}

const BoardPosition &Board::getActiveBlockPosition() const
{
    return activeBlockPosition;
}

const Block &Board::getActiveBlock() const
{
    return activeBlock;
}

unsigned int Board::getHeight() const
{
    return HEIGHT;
}

unsigned int Board::getWidth() const
{
    return WIDTH;
}

BlockType Board::getBlockTypeAt(BoardPosition position) const
{
    if (!isPositionValid(position)){
        throw std::invalid_argument("Received invalid position");
    }
    return blockTypes[position.row][position.col];
}

void Board::clearPosition(BoardPosition position)
{
    if (!isPositionValid(position)){
        throw std::invalid_argument("Received invalid position");
    }
    board[position.row][position.col] = false;
    blockTypes[position.row][position.col] = BlockType(0);
}

void Board::clearRow(unsigned int row)
{
    if (row >= HEIGHT){
        throw std::invalid_argument("Received invalid row");
    }
    for (unsigned int col = 0; col < WIDTH; ++col)
        clearPosition(BoardPosition(row, col));
}

void Board::clearBoard()
{
    for (unsigned int row = 0; row < HEIGHT; ++row)
        clearRow(row);
}

bool Board::isCellFull(BoardPosition position) const
{
    if (!isPositionValid(position)){
        throw std::invalid_argument("Received invalid position");
    }
    return board[position.row][position.col];
}

bool Board::isCellFree(BoardPosition position) const
{
    if (!isPositionValid(position)){
        return false;
    }
    return !board[position.row][position.col];  //TODO fix overflow which happens when this returns false
}

bool Board::isRowFree(unsigned int row) const
{
    if (row >= HEIGHT){
        throw std::invalid_argument("Received invalid row");
    }
    for (unsigned int col = 0; col < WIDTH; ++col)
        if (!isCellFree(BoardPosition(row, col)))
            return false;

    return true;
}

bool Board::isRowFull(unsigned int row) const
{
    if (row >= HEIGHT){
        throw std::invalid_argument("Received invalid row");
    }
    for (unsigned int col = 0; col < WIDTH; ++col)
        if (isCellFree(BoardPosition(row, col)))
            return false;

    return true;
}

bool Board::doesNotCollideWithBoard(Block newBlock, BoardPosition newPosition) const
{
    // if (!isPositionValid(newPosition)) return false;     // repairs board collision problems, I hope that it wasnt important

    for (unsigned int row = 0; row < newBlock.getMatrix().size(); ++row)
    {
        for (unsigned int col = 0; col < newBlock.getMatrix()[row].size(); ++col)
        {
            if (!newBlock.getMatrix()[row][col])
                continue;

            BoardPosition actualPosition(newPosition.row + row, newPosition.col + col);
            if (!isPositionValid(actualPosition) || !isCellFree(actualPosition)){
                return false;
            }
        }
    }

    return true;
}

bool Board::canAddNewBlock(BlockType type) const
{
    return doesNotCollideWithBoard(Block(type), startingPosition);
}

bool Board::attemptToAddNewBlock(BlockType type) // dodawanie klocka na pozycję startową (false - nie można dodać)
{
    if (canAddNewBlock(type))
    {
        setNewBlock(type);
        return true;
    }
    return false;
}

bool Board::canMoveBlock(MoveDirection direction) const
{
    BoardPosition positionCopy = activeBlockPosition;
    positionCopy.move(direction);

    return doesNotCollideWithBoard(activeBlock, positionCopy);
}

bool Board::attemptToMoveActiveBlock(MoveDirection direction)
{
    if (canMoveBlock(direction))
    {
        activeBlockPosition.move(direction);
        return true;
    }
    return false;
}

bool Board::canRotateActiveBlock(RotationDirection direction) const
{
    Block blockCopy = activeBlock;
    blockCopy.rotate(direction);

    return doesNotCollideWithBoard(blockCopy, activeBlockPosition);
}

bool Board::attemptToRotateActiveBlock(RotationDirection direction)
{
    if (canRotateActiveBlock(direction))
    {
        activeBlock.rotate(direction);
        return true;
    }
    return false;
}

void Board::dropRow(unsigned int row) // spuszczanie wiersza niżej jeśli pod nim jest pusto
{
    if (row >= HEIGHT - 1){
        throw std::invalid_argument("Received invalid row");
    }

    if (!isRowFree(row + 1))
        return;

    for (unsigned int col = 0; col < WIDTH; ++col)
    {
        board[row + 1][col] = board[row][col];
        blockTypes[row + 1][col] = blockTypes[row][col];
    }

    clearRow(row);
}

void Board::removeRow(unsigned int row)
{
    if (row >= HEIGHT){
        throw std::invalid_argument("Received invalid row");
    }

    clearRow(row);

    for (int cRow = row - 1; cRow >= 0; --cRow)
        dropRow(cRow);
}

unsigned int Board::fixBoard() // usuwanie tych wiersz, które są pełne i spuszczanie tych pod którymi jest pusto
{
    unsigned int countDeletedRows = 0;

    for (unsigned int row = 0; row < HEIGHT; ++row)
        while (isRowFull(row))
        {
            removeRow(row);
            ++countDeletedRows;
        }
    return countDeletedRows;
}

bool Board::attemptToSolidify()
{
    if (!doesNotCollideWithBoard(activeBlock, activeBlockPosition))
        return false;

    auto blockMatrix = activeBlock.getMatrix();

    for (unsigned int row = 0; row < blockMatrix.size(); ++row)
    {
        for (unsigned int col = 0; col < blockMatrix[row].size(); ++col)
        {
            if (!blockMatrix[row][col])
                continue;

            BoardPosition posOnBoard(activeBlockPosition.row + row, activeBlockPosition.col + col);

            board[posOnBoard.row][posOnBoard.col] = true;
            blockTypes[posOnBoard.col][posOnBoard.row] = activeBlock.getType();
        }
    }
    hasActiveBlock = false;
    return true;
}
