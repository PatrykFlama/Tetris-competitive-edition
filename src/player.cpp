#include "player.h"

Player::Player(PlayerType _playerType) : player_type(_playerType) {}

Move Player::getMove(){
    int key = getch();

    /*
    p1/p2:
    ad/arrows - left right
    sw/arrows - down slow fast
    c/'/' - holding cell
    qe/<> - rotate c ccw
    */

    if(player_type == HUMAN1){     // player 1
        switch (key)
        {
            case 'a':
                return MOVE_LEFT;
                break;
            case 'd':
                return MOVE_RIGHT;
                break;
            case 's':
                return SLOW_DOWN;
                break;
            case 'w':
                return FAST_DOWN;
                break;
            case 'q':
                return ROTATE_COUNTERCLOCKWISE;
                break;
            case 'e':
                return ROTATE_CLOCKWISE;
                break;
            case 'c':
                return TO_HOLDING_CELL;
                break;
            
            default:
                return NONE;
                break;
        }
    } else if(player_type == HUMAN2){      // player 2
        switch (key)
        {
           case KEY_LEFT:
                return MOVE_LEFT;
                break;
            case KEY_RIGHT:
                return MOVE_RIGHT;
                break;
            case KEY_DOWN:
                return SLOW_DOWN;
                break;
            case KEY_UP:
                return FAST_DOWN;
                break;
            case ',':       // <
                return ROTATE_COUNTERCLOCKWISE;
                break;
            case '.':       // >
                return ROTATE_CLOCKWISE;
                break;
            case '/':
                return TO_HOLDING_CELL;
                break;
            
            default:
                return NONE;
                break;
        }
    } else{         // bot
        // TODO return bot input
        return NONE;
    }
}
