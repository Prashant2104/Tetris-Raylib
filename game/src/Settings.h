#pragma once
#include "Vec2.h"

namespace Settings {
    //Window Settings
    inline constexpr int screenWidth = 800;
    inline constexpr int screenHeight = 720;
    inline constexpr int fps = 60;
    inline constexpr char* title = "Tetris";

    //Board Settings
    inline constexpr int cellSize = 30;
    inline constexpr int padding = 1;
    inline constexpr Vec2<int> boardPosition{ 60,60 };
    inline constexpr Vec2<int> boardSize{ 10,20 };
}