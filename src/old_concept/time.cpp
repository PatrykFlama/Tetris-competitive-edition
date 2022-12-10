#include "headers.h"

struct Time{
    int framerate;      // !frames per second
    int time_start;
    int last_block_movement;    // this probably should be in game structure, but at this point in time it is nonexistent
    const int M = 1e7;

    Time() : Time(30, 1000){}
    Time(int _framerate, int game_start_delay) : framerate(_framerate), time_start(time()){
        last_block_movement = time() + game_start_delay;
    }

    int time() {
        return (chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count()) % M;
    }

    // int ticks(){
    //     return ((time()-time_start)*framerate)/1000;
    // }

    // int restart_time(){
    //     time_start = time();
    // }

    bool should_block_fall(int blocks_falling_speed){    // this probably should be in game structure, but at this point in time it is nonexistent
        if(blocks_falling_speed < time() - last_block_movement){
            last_block_movement += blocks_falling_speed;
            return true;
        }
        return false;
    }
};