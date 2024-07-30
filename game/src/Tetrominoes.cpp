#include "Tetrominoes.h"
#include "Settings.h"
#include <iostream>

//Tetromino::Tetromino() :
//    dimension(0),
//    shape(false),
//    color(BLACK),
//    boardPos(Settings::boardSize.GetX() / 2 - dimension / 2, 0),
//    currentRotation(Rotation::UP)
//{
//    currentPosition = boardPos;
//    fallCounter = 0;
//    fallMultiplier = 1;
//    bottomedOut = false;
//    boardSize = Settings::boardSize;
//    cellSize = Settings::cellSize;
//}
Tetromino::Tetromino(const bool* shape, int dimension, Color color) :
    shape(shape),
    dimension(dimension),
    color(color),
    boardPos(Settings::boardSize.GetX() / 2 - dimension / 2, 0),
    currentRotation(Rotation::UP)
{
    currentPosition = boardPos;
    fallCounter = 0;
    fallMultiplier = 1;
    bottomedOut = false;
    boardSize = Settings::boardSize;
    cellSize = Settings::cellSize;
}

void Tetromino::RotateClockwise()
{
    if (bottomedOut) return;
    int rightDist = currentPosition.GetX() + dimension - boardSize.GetX();
    if (rightDist > 0) {
        for (int i = 0; i < rightDist; i++)
        {
            MoveLeft();
        }
    }
    int leftDist = -currentPosition.GetX();
    if (leftDist > 0) {
        for (int i = 0; i < leftDist; i++)
        {
            MoveRight();
        }
    }
    currentRotation = Rotation((int(currentRotation) + 1) % 4);;
}

void Tetromino::RotateCounterClockwise()
{
    if (bottomedOut) return;
    int rightDist = currentPosition.GetX() + dimension - boardSize.GetX();
    if (rightDist > 0) {
        for (int i = 0; i < rightDist; i++)
        {
            MoveLeft();
        }
    }
    int leftDist = -currentPosition.GetX();
    if (leftDist > 0) {
        for (int i = 0; i < leftDist; i++)
        {
            MoveRight();
        }
    }
    currentRotation = Rotation((int(currentRotation) + 3) % 4);
}

void Tetromino::MoveLeft()
{
    if (bottomedOut) return;

    int distance = -currentPosition.GetX();
    if (distance < 0) {
        currentPosition.SetX(currentPosition.GetX() - 1);
        return;
    }
    else if (CheckLeftCollision(distance + 1)) {
        currentPosition.SetX(currentPosition.GetX() - 1);
        return;
    }
    std::cout << "Left" << std::endl;
}

void Tetromino::MoveRight()
{
    if (bottomedOut) return;
    int distance = currentPosition.GetX() + dimension - boardSize.GetX();
    if (distance < 0) {
        currentPosition.SetX(currentPosition.GetX() + 1);
        return;
    }
    else if (CheckRightCollision(distance + 1)) {
        currentPosition.SetX(currentPosition.GetX() + 1);
        return;
    }
    std::cout << "Right" << std::endl;
}

void Tetromino::Falling()
{
    if (bottomedOut) return;
    fallCounter += GetFrameTime() * fallMultiplier;
    if (fallCounter >= Settings::fallTime) {
        fallCounter = 0;

        int distance = currentPosition.GetY() + dimension - boardSize.GetY();
        if (distance < 0) {
            currentPosition.SetY(currentPosition.GetY() + 1);
            return;
        }
        else if (CheckBottomCollision(distance + 1)) {
            currentPosition.SetY(currentPosition.GetY() + 1);
            return;
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
                DrawCell(currentPosition + Vec2<int>{x, y}, color);
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
    if (layerFromBottom == 0) return true;

    for (int i = 0; i < dimension; i++) {
        bool isCellFilled = false;
        switch (currentRotation)
        {
        case Tetromino::Rotation::UP:
            isCellFilled = shape[i + (dimension * (dimension - layerFromBottom))];
            break;
        case Tetromino::Rotation::RIGHT:
            isCellFilled = shape[dimension * dimension - (dimension * i) - layerFromBottom];
            break;
        case Tetromino::Rotation::DOWN:
            isCellFilled = shape[dimension * layerFromBottom - 1 - i];
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
    if (layerFromLeft == 0) return true;
    layerFromLeft -= 1;
    for (int i = 0; i < dimension; i++) {
        bool isCellFilled = false;
        switch (currentRotation)
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
    if (layerFromRight == 0) return true;
    layerFromRight -= 1;
    for (int i = 0; i < dimension; i++) {
        bool isCellFilled = false;
        switch (currentRotation)
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

void Tetromino::DrawCell(Vec2<int> pos, Color color) const
{
    assert(pos.GetX() >= 0 && pos.GetY() >= 0 && pos.GetX() < boardSize.GetX() && pos.GetY() < boardSize.GetY());
    Vec2<int> topLeft = Settings::boardPosition + Settings::padding + (pos * cellSize);
    raycpp::DrawRectangle(topLeft, Vec2<int>{ cellSize, cellSize} - Settings::padding, color);
}
