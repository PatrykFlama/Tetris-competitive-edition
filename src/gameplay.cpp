#include "gameplay.h"

Gameplay::Gameplay(Player _player, unsigned int boardHeight, unsigned int boardWidth) : player(_player),
                                                                                        board(boardHeight, boardWidth),
                                                                                        blocksQueuePointer(0),
                                                                                        difficultyLevel(0),
                                                                                        isGameOver(false),
                                                                                        isStoredBlock(false)
{
    for (unsigned int i = 0; i < 2; i++)
        for (unsigned int type = 0; type < 7; type++)
        {
            BlockType blockType = static_cast<BlockType>(type);
            blocksQueue.push_back(blockType);
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
    if (!board.canMoveBlock(DOWN))
    {
        board.attemptToSolidify();
        unsigned int lines_broken = board.fixBoard();
        score.blockDropped(lines_broken, false);
        spawnBlock();
    }
}

void Gameplay::makePlayerMove()
{
    Move move = player.getMove();

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
        BlockType activeBlock = board.getActiveBlock().getType();
        if(isStoredBlock) board.setNewBlock(storedBlock);
        else{
            isStoredBlock = true;
            board.setNewBlock(blocksQueue[blocksQueuePointer++]);
            if (blocksQueuePointer >= blocksQueue.size())
                redrawBlocks();
        }
        storedBlock = activeBlock;
        break;

    default:
        break;
    }
}

void Gameplay::setDifficultyLevel(unsigned int new_difficulty)
{
    difficultyLevel = new_difficulty;
}

void Gameplay::onGameOver()
{
    isGameOver = true;
}

void Gameplay::gameLoop()
{
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

const Board &Gameplay::getBoard() const
{
    return board;
}
