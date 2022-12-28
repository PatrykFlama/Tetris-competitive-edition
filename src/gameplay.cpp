#include "block.h"
#include "board.h"
#include "gameplay.h"

Gameplay::Gameplay() : Gameplay(standardHEIGHT, standardWIDTH) {}

Gameplay::Gameplay(int boardHeight, int boardWidth) :
    board(boardHeight, boardWidth),
    difficulty_level(0),
    combo(0),
    blocksQueuePointer(0),
    isGameOver(false)
{
    for(int i = 0; i < 2; i++)
        for(int type = 0; type < 7; type++){
            BlockType block = static_cast<BlockType>(type);
            blocksQueue.push_back(block);
        }
}

void Gameplay::redrawBlocks(){
    std::random_shuffle(blocksQueue.begin(), blocksQueue.end());
    blocksQueuePointer = 13;
}

bool Gameplay::spawnBlock(){
    if(blocksQueuePointer < 0) redrawBlocks();
    if(!board.attemptToAddeBlock(blocksQueue[blocksQueuePointer--])){
        isGameOver = true;
    }
}

void Gameplay::onGameTick(){
    if(!board.canMoveBlock(DOWN)){      //! TODO: make it accessible
        uint linesBroken = board.fixBoard();        //! TODO: make it accessible
        // score.addScore(linesBroken); (or smth like that)
        spawnBlock();
    }
}

void Gameplay::makePlayerMove(){
    /* concept
    if(player.getInput != NONE){
        MAKE_MOVE
    }
    */
}

void Gameplay::changeDiffLevel(int new_difficulty){
    difficulty_level = new_difficulty;
    // TODO: time.changeTickrate(difficulty_level);
}

void Gameplay::gameOver(){
    // time.stop;
}

void Gameplay::gameLoop(){
    makePlayerMove();
    // TODO: if(time.nextTick()){
        onGameTick();
        if(gameOver) gameOver();
    // }
}

bool Gameplay::isLost() const{
    return isGameOver;
}

int Gameplay::returnScore() const{
    // return Score.score;
}

int Gameplay::returnDiffLevel() const{
    return difficulty_level;
}
