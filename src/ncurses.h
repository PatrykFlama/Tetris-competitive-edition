#define ncurses false
#define initscr()                               //? ncruses
#define printw(...) printf(__VA_ARGS__)         //? ncruses            
#define scanw(...) scanf(__VA_ARGS__)           //? ncurses 
#define getch() getchar()                       //? ncruses       
#define refresh()                               //? ncruses
#define clear() printf("\e[1;1H\e[2J");         //? ncruses                    
#define endwin()                                //? ncruses
#define start_color()                           //? ncruses
#define init_pair(index, foreground, background)//? ncruses
#define init_color(color, R, G, B)              //? ncruses from [0, 1000]
#define attron(...)                             //? ncruses
#define attroff(...)                            //? ncruses
#define keypad(...)

#define KEY_UP 'k'
#define KEY_DOWN 'k'
#define KEY_LEFT 'k'
#define KEY_RIGHT 'k'
#define KEY_ENTER 'k'

#define noecho()
#define curs_set(...)
#define getmaxyx(...)
#define mvprintw(...)
#define timeout(...)
#define cbreak()