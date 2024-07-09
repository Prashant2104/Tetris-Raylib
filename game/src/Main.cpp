#include "Game.h"
#include "Settings.h"

//----------------------------------------------------------------------------------
// Main Entry Point
//----------------------------------------------------------------------------------
int main()
{
    Game game(Settings::screenWidth, Settings::screenHeight, Settings::fps, Settings::title);

    while (!game.GameShouldClose())
    {
        game.Tick();
    }

    return 0;
}