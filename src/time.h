#ifndef TIME_H
#define TIME_H
#include <time.h>

class Time {
    int framerate;
    int time_start;
    int game_start_delay;
    
public:
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
    Time(int _framerate, int _time_start, int _game_start_delay);
	int getSystemTime();
	int getLastDropTime();
	int getDropSpeed();
};

#endif
