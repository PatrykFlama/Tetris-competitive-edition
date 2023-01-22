#include "game_time.h"
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

const unsigned int M = 1e7;

unsigned int Time::getSystemTime()
{
	unsigned int systemTime = std::chrono::duration_cast<millis>(std::chrono::system_clock::now().time_since_epoch()).count() % M;
	return systemTime;
}

unsigned int Time::convertTime(millis T)
{
	unsigned int convertedT = std::chrono::duration_cast<millis>(T).count() % M;
	return convertedT;
}

Time::Time(unsigned int *_difficulty_level, unsigned int _framerate, millis _game_start_delay) : framerate(_framerate), time_start(getSystemTime()), game_start_delay(_game_start_delay), difficultyLevel(_difficulty_level)
{
	last_block_movement = (getSystemTime() + convertTime(_game_start_delay)) % M;
	block_drop_speed.resize(30);
	block_drop_speed[0] = 800ms, block_drop_speed[1] = 720ms, block_drop_speed[2] = 630ms, block_drop_speed[3] = 550ms, block_drop_speed[4] = 470ms,
	block_drop_speed[5] = 380ms, block_drop_speed[6] = 300ms, block_drop_speed[7] = 220ms, block_drop_speed[8] = 130ms, block_drop_speed[9] = 100ms,
	block_drop_speed[10] = 80ms, block_drop_speed[11] = 80ms, block_drop_speed[12] = 80ms, block_drop_speed[13] = 70ms, block_drop_speed[14] = 70ms,
	block_drop_speed[15] = 70ms, block_drop_speed[16] = 50ms, block_drop_speed[17] = 50ms, block_drop_speed[18] = 50ms, block_drop_speed[29] = 20ms;
	for (unsigned int level = 19; level <= 29; level++)
		block_drop_speed[level] = 30ms;
}

unsigned int Time::getLastBlockMovement()
{
	return last_block_movement;
}

unsigned int Time::getDropSpeed()
{
	if (*difficultyLevel > 29)
		return convertTime(block_drop_speed[29]);
	return convertTime(block_drop_speed[*difficultyLevel]);
}

bool Time::shouldBlockFall()
{
	if (getSystemTime() - last_block_movement >= getDropSpeed())
	{
		last_block_movement = getSystemTime();
		return true;
	}
	return false;
}
