#ifndef TIME_H
#define TIME_H
#include <chrono>
#include <vector>

#define BLOCKDROPSPEEDSIZE 30
typedef std::chrono::milliseconds milliseconds;
typedef unsigned int uint;

class Time {
private:
    uint time_start;
    uint last_block_movement;
    uint *difficulty_level;
    std::vector<milliseconds> block_drop_speed;
    uint getSystemTime();
    uint getDropSpeed();
    
public:
    Time(uint *_difficulty_level);
	uint convertTime(milliseconds _T);
	bool shouldBlockFall();
};

#endif
