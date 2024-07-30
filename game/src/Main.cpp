#include "raylib.h"
#include "Settings.h"
#include "Game.h"
void main() {
	Game game(Settings::screenWidth, Settings::screenHeight, Settings::fps, Settings::title);

	while (!game.GameShouldClose())
	{
		game.Tick();
	}
}