#include <assert.h>
#include "Game.h"
#include "raylib.h"
#include "Board.h"
#include "Settings.h"

Board board(Settings::boardPosition,
    Settings::boardSize,
    Settings::cellSize,
    Settings::padding);

Game::Game(int width, int height, int fps, char* title) :
    tetromino(board)
{
    assert(!GetWindowHandle()); //If assertion triggers: Window is already open
    InitWindow(width, height, title);
    SetTargetFPS(fps);
}

Game::~Game() noexcept
{
    CloseWindow();
}

bool Game::GameShouldClose() const
{
    assert(GetWindowHandle()); //If assertion triggers: Window is already closed
    return WindowShouldClose();
}

void Game::Tick()
{
    BeginDrawing();

    Update();
    Draw();

    EndDrawing();
}

void Game::Draw()
{
    ClearBackground(RAYWHITE);
    board.Draw();
    tetromino.Draw();
}

void Game::Update()
{
    if (IsKeyPressed(KEY_E))
        tetromino.RotateClockwise();
    if (IsKeyPressed(KEY_Q))
        tetromino.RotateCounterClockwise();
}