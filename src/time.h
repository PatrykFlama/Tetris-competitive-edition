#ifndef TIME_H
#define TIME_H
#include <chrono>
#include <vector>

#define BLOCKDROPSPEEDSIZE 30
typedef std::chrono::milliseconds milliseconds;
typedef unsigned int uint;

class Time {
private:
    int framerate;
    int time_start;
    milliseconds game_start_delay;
    int last_block_movement;
    int *difficulty_level;
    std::vector<milliseconds> block_drop_speed;
    int getSystemTime();
    int getLastDropTime();
    int getDropSpeed();
    int getLastBlockMovement();
    
public:
	Time(int *_difficulty_level);
    Time(int *_difficulty_level, int _framerate, milliseconds _game_start_delay);
	int convertTime(milliseconds _T);
	bool shouldBlockFall();
};

#endif
