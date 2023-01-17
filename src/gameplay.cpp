#include "gameplay.h"

Gameplay::Gameplay(Player _player) : Gameplay(_player, standardHEIGHT, standardWIDTH) {}

Gameplay::Gameplay(Player _player, uint boardHeight, uint boardWidth) :
    player(_player),
    board(boardHeight, boardWidth),
    difficulty_level(0),
    blocksQueuePointer(0),
    isGameOver(false),
    time(&difficulty_level)
{
    for(uint i = 0; i < 2; i++)
        for(uint type = 0; type < 7; type++){
            BlockType block = static_cast<BlockType>(type);
            blocksQueue.push_back(block);
        }
}

void Gameplay::redrawBlocks(){
    std::random_shuffle(blocksQueue.begin(), blocksQueue.end());
    blocksQueuePointer = 13;
}

void Gameplay::spawnBlock(){
    if(blocksQueuePointer < 0) redrawBlocks();
    if(!board.attemptToAddeBlock(blocksQueue[blocksQueuePointer--])){
        isGameOver = true;
    }
}

void Gameplay::onGameTick(){
    if(!board.canMoveBlock(DOWN)){
        board.setOnBoard();
        uint lines_broken = board.fixBoard();
        score.blockDropped(lines_broken, false);
        spawnBlock();
    }
}

void Gameplay::makePlayerMove(){
    Move move = player.getInput();

    switch (move){
        case MOVE_LEFT:
            board.attemptToMoveBlock(LEFT);
            break;
        case MOVE_RIGHT:
            board.attemptToMoveBlock(RIGHT);
            break;
        case SLOW_DOWN:
            board.attemptToMoveBlock(DOWN);
            break;
        case FAST_DOWN:
            while(board.attemptToMoveBlock(DOWN)){}
            board.setOnBoard();
            // ui update for pleasent visuals
            uint lines_broken = board.fixBoard();
            score.blockDropped(lines_broken, true);
            break;
        case ROTATE_COUNTERCLOCKWISE:
            board.attemptToRotateBlock(COUNTERCLOCKWISE);
            break;
        case ROTATE_CLOCKWISE:
            board.attemptToRotateBlock(CLOCKWISE);
            break;
        case TO_HOLDING_CELL:
            board.storeBlock();// TODO - store active block and change it with stored one (if exists)
            break;
        
        default:
            break;
    }

    if(move != NONE){} // TODO refresh UI
}

void Gameplay::changeDiffLevel(uint new_difficulty){
    difficulty_level = new_difficulty;
}

void Gameplay::gameOver(){
	
}

void Gameplay::gameLoop(){
    makePlayerMove();
    if(time.shouldBlockFall()) {
        onGameTick();
        if(gameOver) gameOver();
    }
}

bool Gameplay::isLost() const{
    return isGameOver;
}

uint Gameplay::returnScore() const{
    return score.returnScore();
}

uint Gameplay::returnDiffLevel() const{
    return difficulty_level;
}
