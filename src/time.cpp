#include "Time.h"
#include <gameplay.h>
#include <chrono>
#include <time.h>

const int M = 1e7;

int Time::getSystemTime() {
	int systemTime = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count()) % M;
	return systemTime;
}

Time::Time(int _framerate, int _time_start, int game_start_delay) : framerate(_framerate), time_start(getSystemTime()){
	last_block_movement = time() + game_start_delay;
}

int Time::getLastDropTime() {
	// TODO
}

int Time::getDropSpeed() {
	// TODO
}

bool should_block_fall(int blocks_falling_speed){
	if(blocks_falling_speed < getSystemTime() - last_block_movement){
		last_block_movement += blocks_falling_speed;
		return true;
	}
	return false;
}
