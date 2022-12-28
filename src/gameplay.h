#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "block.h"
#include "board.h"

#include <vector>
#include <algorithm>

class Gameplay{
    Board board;
    // Score score; // TODO: class for scoring system
    // Time time; // TODO: class for time management
    // Player player; // TODO: class for player input
    std::vector<BlockType> blocksQueue;    // queue for next blocks, size 2*7
    int blocksQueuePointer;
    int difficulty_level;
    /*
    Level         Drop speed (frames/line)
     00            48 (0.8 s)
     01            43 (0.72s)
     02            38 (0.63s) 
     03            33 (0.55s) 
     04            28 (0.47s) 
     05            23 (0.38s)
     06            18 (0.3 s) 
     07            13 (0.22s)
     08             8 (0.13s)
     09             6 (0.1 s)
     10-12          5 (0.08s) 
     13-15          4 (0.07s)
     16-18          3 (0.05s)
     19-28          2 (0.03s)
     29+            1 (0.02s)
    */
    int combo;      // line breaks combo counter
    bool isGameOver;      // is the game lost/over

    //? ------ GAMEPLAY MECHANICS ------
    void redrawBlocks();    // put new set of blocks to queue
    bool spawnBlock();     // spawn new block from queue, false if cant spawn block == game over
    void makePlayerMove();      // TODO: try to execute player move, if there is one
    void onGameTick();      // try to fall block, solidify block, break lines, count score, etc;
    void gameOver();        // execute game over stuff, called upon game over
    void gameLoop();        // merge all game stuff to do

    //? ------ EXTERNAL GAMEPLAY MANAGEMENT ------
    void changeDiffLevel(int new_difficulty);       // change difficulty level
    //void syncGameClock(bool sync);                  // true - game will use its internal action tick, false - game will use tick() function as tick
    
public:
    Gameplay();
    Gameplay(int boardHeight, int boardWidth);
    // Gameplay(Player *_player);
    
    bool isLost() const;     // is the game lost
    int returnScore() const;    // TODO: return game score
    int returnDiffLevel() const;    // return difficulty level
    
};

#endif
