#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "block.h"
#include "board.h"
#include "player.h"
#include "time.h"
#include "score.h"

#include <vector>
#include <algorithm>

class Gameplay
{
    Player player;
    Board board;
    Time time;
    Score score;
    BlockType holdingCell;
    std::vector<BlockType> blocksQueue;
    unsigned int blocksQueuePointer;

    unsigned int difficultyLevel;
    bool isGameOver;

    void redrawBlocks();
    void spawnBlock();
    bool makePlayerMove();
    void onGameTick();
    void onGameOver();
    void setDifficultyLevel(unsigned int newDifficultyLevel);

public:
    Gameplay(Player _player, unsigned int boardHeight = DEFAULT_BOARD_HEIGHT, unsigned int boardWidth = DEFAULT_BOARD_WIDTH);

    bool gameLoop();        // return true if ui should be updated (action happened)
    bool getGameOver() const;
    unsigned int getScore() const;
    unsigned int getDifficultyLevel() const;

    const BlockType &getNextBlockType() const;
    const BlockType getHoldingCellBlockType() const;
    const Board &getBoard() const;
};

#endif
