#include "Tetrominoes.h"
#include "Settings.h"

Tetromino::Tetromino(const bool* shape, int dimension, Color color, const Board& board) :
    shape(shape),
    dimension(dimension),
    color(color),
    boardPos(board.GetBoardSize().GetX() / 2 - dimension / 2, 0),
    board(board),
    currentRotation(Rotation::UP)
{
    currentPosition = boardPos;
    fallCounter = 0;
}

void Tetromino::RotateClockwise()
{
    currentRotation = Rotation((int(currentRotation) + 1) % 4);
}

void Tetromino::RotateCounterClockwise()
{
    currentRotation = Rotation((int(currentRotation) + 3) % 4);
}

void Tetromino::MoveLeft()
{
    if (currentPosition.GetX() > 0) {
        currentPosition.SetX(currentPosition.GetX() - 1);
    }
}

void Tetromino::MoveRight()
{
    if (currentPosition.GetX() + dimension < board.GetBoardSize().GetX()) {
        currentPosition.SetX(currentPosition.GetX() + 1);
    }
}

void Tetromino::Falling()
{
    fallCounter += GetFrameTime();
    if (fallCounter >= Settings::fallTime) {
        fallCounter = 0;
        if (currentPosition.GetY() + dimension < board.GetBoardSize().GetY()) {
            currentPosition.SetY(currentPosition.GetY() + 1);
        }
    }
}

void Tetromino::Draw() const
{
    for (int y = 0; y < dimension; y++) {
        for (int x = 0; x < dimension; x++) {
            bool cell = false;
            switch (currentRotation)
            {
            case Tetromino::Rotation::UP:
                cell = shape[y * dimension + x];
                break;
            case Tetromino::Rotation::RIGHT:
                cell = shape[dimension * (dimension - 1) - dimension * x + y];
                break;
            case Tetromino::Rotation::DOWN:
                cell = shape[(dimension * dimension - 1) - dimension * y - x];
                break;
            case Tetromino::Rotation::LEFT:
                cell = shape[dimension - 1 + dimension * x - y];
                break;
            default:
                break;
            }
            if (cell)
            {
                board.DrawCell(currentPosition + Vec2<int>{x, y}, color);
            }
        }
    }
}
