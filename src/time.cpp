#include "time.h"
#include <chrono>

using namespace std::chrono_literals;

/*
    Level         Drop speed (frames/line)
     00            48 (0.8 s)
     01            43 (0.72s)
     02            38 (0.63s) 
     03            33 (0.55s) 
     04            28 (0.47s) 
     05            23 (0.38s)
     06            18 (0.3 s) 
     07            13 (0.22s)
     08             8 (0.13s)
     09             6 (0.1 s)
     10-12          5 (0.08s) 
     13-15          4 (0.07s)
     16-18          3 (0.05s)
     19-28          2 (0.03s)
     29+            1 (0.02s)
    */

const uint M = 1e7;

uint Time::getSystemTime() {
	uint systemTime = std::chrono::duration_cast<milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() % M;
	return systemTime;
}

uint Time::convertTime(milliseconds T) {
	uint convertedT = std::chrono::duration_cast<milliseconds>(T).count() % M;
	return convertedT;
}

Time::Time(uint *_difficulty_level) : time_start(getSystemTime()), difficulty_level(_difficulty_level){
	last_block_movement = (getSystemTime()) % M;
	block_drop_speed.resize(30);
	block_drop_speed[0] = 800ms, block_drop_speed[1] = 720ms, block_drop_speed[2] = 630ms, block_drop_speed[3] = 550ms, block_drop_speed[4] = 470ms, 
	block_drop_speed[5] = 380ms, block_drop_speed[6] = 300ms, block_drop_speed[7] = 220ms, block_drop_speed[8] = 130ms, block_drop_speed[9] = 100ms,
	block_drop_speed[10] = 80ms, block_drop_speed[11] = 80ms, block_drop_speed[12] = 80ms, block_drop_speed[13] = 70ms, block_drop_speed[14] = 70ms,
	block_drop_speed[15] = 70ms, block_drop_speed[16] = 50ms, block_drop_speed[17] = 50ms, block_drop_speed[18] = 50ms, block_drop_speed[29] = 20ms;
	for (uint level = 19; level <= 29; level ++) block_drop_speed[level] = 30ms;
}

uint Time::getLastBlockMovement() {
	return last_block_movement;
}

uint Time::getDropSpeed() {
	if (*difficulty_level > 29) return convertTime(block_drop_speed[29]);
	return convertTime(block_drop_speed[*difficulty_level]);
}

bool Time::shouldBlockFall() {
	if (getSystemTime() - last_block_movement >= getDropSpeed()) {
		last_block_movement = getSystemTime();
		return true;
	}
	return false;
}
