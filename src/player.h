#ifndef PLAYER_H
#define PLAYER_H

enum PlayerType
{
    HUMAN,
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
public:
    Player(PlayerType _playerType);
};

#endif
