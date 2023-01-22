#ifndef GAME_TIME_H
#define GAME_TIME_H
#include <chrono>
#include <vector>

#define BLOCKDROPSPEEDSIZE 30
typedef std::chrono::milliseconds millis;

class Time {
private:
    unsigned int framerate;
    unsigned int time_start;
    millis game_start_delay;
    unsigned int last_block_movement;
    unsigned int *difficultyLevel;
    std::vector<millis> block_drop_speed;
    unsigned int getSystemTime();
    unsigned int getLastDropTime();
    unsigned int getDropSpeed();
    unsigned int getLastBlockMovement();
    
public:
	Time(unsigned int *_difficulty_level);
    Time(unsigned int *_difficulty_level, unsigned int _framerate, millis _game_start_delay);
	unsigned int convertTime(millis _T);
	bool shouldBlockFall();
};

#endif
