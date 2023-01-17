#ifndef SCORE_H
#define SCORE_H

typedef unsigned int uint;

class Score
{
    uint score;     // total score
    uint combo;      // line breaks in row combo counter
    uint tetris_combo; // how many tetrises in row
    uint *difficulty_level;
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

    const uint hard_drop_points = 10;
    const float difficulty_multiplier = 0.2;
    const uint lines_points[4] = {100, 300, 500, 800};
    const uint tetris_combo_points = 200;

public:
    Score(uint *_difficulty_level);

    void blockDropped(uint lines_broken, bool if_hard_drop);    // function to be called upon block fall
    uint returnScore() const;
};

#endif
