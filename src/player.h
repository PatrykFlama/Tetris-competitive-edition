#ifndef PLAYER_H
#define PLAYER_H

enum PlayerType
{
    HUMAN1,
    HUMAN2,
    BOT
};

enum Move
{
    MOVE_LEFT,
    MOVE_RIGHT,
    SLOW_DOWN,
    FAST_DOWN,
    ROTATE_COUNTERCLOCKWISE,
    ROTATE_CLOCKWISE,
    TO_HOLDING_CELL,
    NONE
};

class Player
{
    PlayerType player_type;   // 1, 2, b
public:
    Player(PlayerType _playerType);
    Move getMove();
};

#endif
