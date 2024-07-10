#include "Tetrominoes.h"
#include "Settings.h"
#include <iostream>
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
    fallMultiplier = 1;
    bottomedOut = false;
}

void Tetromino::RotateClockwise()
{
    if (bottomedOut) return;

    Rotation tempRot = Rotation((int(currentRotation) + 1) % 4);

    if (!CheckRightCollision(1) || !CheckLeftCollision(1))
    {
        if (CheckLeftCollision(1)) {
            MoveRight();
        }
        else if (CheckRightCollision(1))
        {
            MoveLeft();
        }
    }
    currentRotation = tempRot;
}

void Tetromino::RotateCounterClockwise()
{
    if (bottomedOut) return;
    if (!CheckRightCollision(1) || !CheckLeftCollision(1))
    {
        if (CheckLeftCollision(1)) {
            MoveRight();
        }
        else if (CheckRightCollision(1))
        {
            MoveLeft();
        }
    }
    currentRotation = Rotation((int(currentRotation) + 3) % 4);
}

void Tetromino::MoveLeft()
{
    if (bottomedOut) return;
    for (int i = 0; i < dimension; i++) {
        if (currentPosition.GetX() + i > 0 && CheckLeftCollision(i)) {
            currentPosition.SetX(currentPosition.GetX() - 1);
            return;
        }
    }
    std::cout << "Left" << std::endl;
}

void Tetromino::MoveRight()
{
    if (bottomedOut) return;
    for (int i = 0; i < dimension; i++) {
        if (currentPosition.GetX() + dimension - i < board.GetBoardSize().GetX() && CheckRightCollision(i)) {
            currentPosition.SetX(currentPosition.GetX() + 1);
            return;
        }
    }
    std::cout << "Right" << std::endl;
}

void Tetromino::Falling()
{
    if (bottomedOut) return;
    fallCounter += GetFrameTime() * fallMultiplier;
    if (fallCounter >= Settings::fallTime) {
        fallCounter = 0;
        for (int i = 0; i < dimension; i++) {
            if (currentPosition.GetY() + dimension - i < board.GetBoardSize().GetY() && CheckBottomCollision(i)) {
                currentPosition.SetY(currentPosition.GetY() + 1);
                return;
            }
        }
        bottomedOut = true;
        std::cout << "Bottom" << std::endl;
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
                cell = shape[(dimension * dimension) - 1 - dimension * y - x];
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

void Tetromino::IncreaseFall(bool fast)
{
    if (fast) {
        fallMultiplier = 10;
    }
    else {
        fallMultiplier = 1;
    }
}

bool Tetromino::CheckBottomCollision(int layerFromBottom)
{
    return CheckBottomCollision(layerFromBottom, currentRotation);
}
bool Tetromino::CheckBottomCollision(int layerFromBottom, Rotation rotation)
{
    if (layerFromBottom == 0) return true;

    for (int i = 0; i < dimension; i++) {
        bool isCellFilled = false;
        switch (rotation)
        {
        case Tetromino::Rotation::UP:
            isCellFilled = shape[i + (dimension * (dimension - layerFromBottom))];
            break;
        case Tetromino::Rotation::RIGHT:
            isCellFilled = shape[dimension * dimension - (dimension * i) - layerFromBottom];
            break;
        case Tetromino::Rotation::DOWN:
            isCellFilled = shape[dimension - layerFromBottom - i];
            break;
        case Tetromino::Rotation::LEFT:
            isCellFilled = shape[dimension * i];
            break;
        default:
            break;
        }
        if (isCellFilled) return false;
    }
    return true;
}

bool Tetromino::CheckLeftCollision(int layerFromLeft)
{
    return CheckLeftCollision(layerFromLeft, currentRotation);
}
bool Tetromino::CheckLeftCollision(int layerFromLeft, Rotation rotation)
{
    if (layerFromLeft == 0) return true;
    layerFromLeft -= 1;
    for (int i = 0; i < dimension; i++) {
        bool isCellFilled = false;
        switch (rotation)
        {
        case Tetromino::Rotation::UP:
            isCellFilled = shape[dimension * i + layerFromLeft];
            break;
        case Tetromino::Rotation::RIGHT:
            isCellFilled = shape[dimension * (dimension - 1) + i - (dimension * layerFromLeft)];
            break;
        case Tetromino::Rotation::DOWN:
            isCellFilled = shape[(dimension * dimension) - 1 - (dimension * i) - layerFromLeft];
            break;
        case Tetromino::Rotation::LEFT:
            isCellFilled = shape[dimension - (i + 1) + (dimension * layerFromLeft)];
            break;
        default:
            break;
        }
        if (isCellFilled) return false;
    }
    return true;
}

bool Tetromino::CheckRightCollision(int layerFromRight)
{
    return CheckRightCollision(layerFromRight, currentRotation);
}
bool Tetromino::CheckRightCollision(int layerFromRight, Rotation rotation)
{
    if (layerFromRight == 0) return true;
    layerFromRight -= 1;
    for (int i = 0; i < dimension; i++) {
        bool isCellFilled = false;
        switch (rotation)
        {
        case Tetromino::Rotation::UP:
            isCellFilled = shape[(dimension - 1) + (dimension * i) - layerFromRight];
            break;
        case Tetromino::Rotation::RIGHT:
            isCellFilled = shape[i + (dimension * layerFromRight)];
            break;
        case Tetromino::Rotation::DOWN:
            isCellFilled = shape[dimension * (dimension - 1) - (dimension * i) + layerFromRight];
            break;
        case Tetromino::Rotation::LEFT:
            isCellFilled = shape[(dimension * dimension) - 1 - i - (dimension * layerFromRight)];
            break;
        default:
            break;
        }
        if (isCellFilled) return false;
    }
    return true;
}
