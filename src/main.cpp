#include "gameplay.h"
#include "player.h"
#include "ui.h"

#include <chrono>
#include <thread>

int main(int argc, char *argv[])
{
    Player p(HUMAN1);
    Gameplay gameplay(p);
    UI ui;
    ui.drawGameplay(gameplay);
    ui.printContents();
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    return 0;
}
