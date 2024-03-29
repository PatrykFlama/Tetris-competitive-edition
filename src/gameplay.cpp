#include "gameplay.h"

Gameplay::Gameplay(Player _player, unsigned int boardHeight, unsigned int boardWidth) : player(_player),
                                                                                        board(boardHeight, boardWidth),
                                                                                        blocksQueuePointer(0),
                                                                                        difficultyLevel(0),
                                                                                        isGameOver(false),
                                                                                        time(&difficultyLevel),
                                                                                        holdingCell(NO_BLOCK)
{
    for (unsigned int i = 0; i < 2; i++){
        for (unsigned int type = 0; type < 7; type++)
        {
            BlockType blockType = static_cast<BlockType>(type);
            blocksQueue.push_back(blockType);
        }
    }
}

void Gameplay::redrawBlocks()
{
    std::random_shuffle(blocksQueue.begin(), blocksQueue.end());
    blocksQueuePointer = 0;
}

void Gameplay::spawnBlock()
{
    if (!board.attemptToAddNewBlock(blocksQueue[blocksQueuePointer++]))
        onGameOver();
    if (blocksQueuePointer >= blocksQueue.size())
        redrawBlocks();
}

void Gameplay::onGameTick()
{
    if (!board.attemptToMoveActiveBlock(DOWN))
    {
        board.attemptToSolidify();
        unsigned int lines_broken = board.fixBoard();
        score.blockDropped(lines_broken, false);
        spawnBlock();
    }
}

bool Gameplay::makePlayerMove()
{
    Move move = player.getMove();
    bool move_made = true;

    switch (move)
    {
        case MOVE_LEFT:
            board.attemptToMoveActiveBlock(LEFT);
            break;
        case MOVE_RIGHT:
            board.attemptToMoveActiveBlock(RIGHT);
            break;
        case SLOW_DOWN:
            board.attemptToMoveActiveBlock(DOWN);
            break;
        case FAST_DOWN:
            while (board.attemptToMoveActiveBlock(DOWN));
            board.attemptToSolidify();
            {
                unsigned int lines_broken = board.fixBoard();
                score.blockDropped(lines_broken, true);
            }
            break;
        case ROTATE_COUNTERCLOCKWISE:
            board.attemptToRotateActiveBlock(COUNTERCLOCKWISE);
            break;
        case ROTATE_CLOCKWISE:
            board.attemptToRotateActiveBlock(CLOCKWISE);
            break;
        case TO_HOLDING_CELL:
            {
                BlockType activeBlock = board.getActiveBlock().getType();
                if(holdingCell != NO_BLOCK) board.setNewBlock(holdingCell);
                else{
                    board.setNewBlock(blocksQueue[blocksQueuePointer++]);
                    if (blocksQueuePointer >= blocksQueue.size())
                        redrawBlocks();
                }
                holdingCell = activeBlock;
                break;
            }
        case NONE:
            move_made = false;
            break;
    }

    return move_made;
}

void Gameplay::setDifficultyLevel(unsigned int new_difficulty)
{
    difficultyLevel = new_difficulty;
}

void Gameplay::onGameOver()
{
    isGameOver = true;
}

bool Gameplay::gameLoop()
{
    bool ui_updated = makePlayerMove();
    if(time.shouldBlockFall()){
        onGameTick();
        ui_updated = true;
    }
    return ui_updated;
}

bool Gameplay::getGameOver() const
{
    return isGameOver;
}

unsigned int Gameplay::getScore() const
{
    return score.getScore();
}

unsigned int Gameplay::getDifficultyLevel() const
{
    return difficultyLevel;
}

const BlockType &Gameplay::getNextBlockType() const
{
    return blocksQueue[blocksQueuePointer];
}

const BlockType Gameplay::getHoldingCellBlockType() const
{
    return holdingCell;
}

const Board &Gameplay::getBoard() const
{
    return board;
}
