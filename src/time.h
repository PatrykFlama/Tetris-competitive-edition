#ifndef TIME_H
#define TIME_H
#include <chrono>
#include <vector>

#define BLOCKDROPSPEEDSIZE 30
typedef std::chrono::milliseconds milliseconds;
typedef unsigned int uint;

class Time {
private:
    uint framerate;
    uint time_start;
    milliseconds game_start_delay;
    uint last_block_movement;
    uint *difficulty_level;
    std::vector<milliseconds> block_drop_speed;
    uint getSystemTime();
    uint getLastDropTime();
    uint getDropSpeed();
    uint getLastBlockMovement();
    
public:
	Time(uint *_difficulty_level);
    Time(uint *_difficulty_level, uint _framerate, milliseconds _game_start_delay);
	uint convertTime(milliseconds _T);
	bool shouldBlockFall();
};

#endif
