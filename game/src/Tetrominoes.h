#pragma once
#include <assert.h>
#include "Vec2.h"
#include "raylibCpp.h"
#include "Board.h"

//Base Class
class Tetromino
{
public:
    enum class Rotation
    {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };
public:
    //Tetromino();
    Tetromino(const bool* shape, int dimension, Color color);
    void RotateClockwise();
    void RotateCounterClockwise();
    void MoveLeft();
    void MoveRight();
    void Falling();
    void Draw() const;
    void IncreaseFall(bool fast);
private:
    Vec2<int> boardPos;
    Vec2<int> boardSize;
    int cellSize;
    Rotation currentRotation;
    const bool* shape;
    const int dimension;
    const Color color;
    Vec2<int> currentPosition;
    float fallCounter;
    float fallMultiplier;
    bool bottomedOut;
private:
    bool CheckBottomCollision(int layerFromBottom);
    bool CheckLeftCollision(int layerFromLeft);
    bool CheckRightCollision(int layerFromRight);
    void DrawCell(Vec2<int> pos, Color color) const;
};

class Straight : public Tetromino
{
public:
    Straight()
        :
        Tetromino(shape, dimension, color)
    {
        static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension);
    }
private:
    static constexpr bool shape[] = { 0,0,0,0,
                                     1,1,1,1,
                                     0,0,0,0,
                                     0,0,0,0 };
    static constexpr int dimension = 4;
    static constexpr Color color = SKYBLUE;
};

class Square : public Tetromino
{
public:
    Square()
        :
        Tetromino(shape, dimension, color)
    {
        static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension);
    }
private:
    static constexpr bool shape[] = { 1,1,
                                     1,1 };
    static constexpr int dimension = 2;
    static constexpr Color color = YELLOW;
};

class Tee : public Tetromino
{
public:
    Tee()
        :
        Tetromino(shape, dimension, color)
    {
        static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension);
    }
private:
    static constexpr bool shape[] = { 0,1,0,
                                     1,1,1,
                                     0,0,0 };
    static constexpr int dimension = 3;
    static constexpr Color color = PURPLE;
};

class Jay : public Tetromino
{
public:
    Jay()
        :
        Tetromino(shape, dimension, color)
    {
        static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension);
    }
private:
    static constexpr bool shape[] = { 1,0,0,
                                     1,1,1,
                                     0,0,0 };
    static constexpr int dimension = 3;
    static constexpr Color color = DARKBLUE;
};

class El : public Tetromino
{
public:
    El()
        :
        Tetromino(shape, dimension, color)
    {
        static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension);
    }
private:
    static constexpr bool shape[] = { 0,0,1,
                                     1,1,1,
                                     0,0,0 };
    static constexpr int dimension = 3;
    static constexpr Color color = ORANGE;
};

class SkewS : public Tetromino
{
public:
    SkewS()
        :
        Tetromino(shape, dimension, color)
    {
        static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension);
    }
private:
    static constexpr bool shape[] = { 0,1,1,
                                     1,1,0,
                                     0,0,0 };
    static constexpr int dimension = 3;
    static constexpr Color color = GREEN;
};

class SkewZ : public Tetromino
{
public:
    SkewZ()
        :
        Tetromino(shape, dimension, color)
    {
        static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension);
    }
private:
    static constexpr bool shape[] = { 1,1,0,
                                     0,1,1,
                                     0,0,0 };
    static constexpr int dimension = 3;
    static constexpr Color color = RED;
};