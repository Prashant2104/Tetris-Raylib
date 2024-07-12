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

    Inputs();
    Update();
    Draw();

    EndDrawing();
}

void Game::Draw()
{
    ClearBackground(RAYWHITE);
    board.Draw();
    for (int i = 0; i < Settings::boardSize.GetY(); i++) {
        for (int j = 0; j < Settings::boardSize.GetX(); j++) {
            board.DrawCell({ j,i }, GetColor(0x0000000f));
        }
    }
    tetromino.Draw();
}

void Game::Update()
{
    tetromino.Falling();
}

void Game::Inputs()
{
    if (IsKeyPressed(KEY_E))
        tetromino.RotateClockwise();
    if (IsKeyPressed(KEY_Q))
        tetromino.RotateCounterClockwise();
    if (IsKeyPressed(KEY_A))
        tetromino.MoveLeft();
    if (IsKeyPressed(KEY_D))
        tetromino.MoveRight();
    if (IsKeyPressed(KEY_S))
        tetromino.IncreaseFall(true);
    if (IsKeyReleased(KEY_S))
        tetromino.IncreaseFall(false);
}
