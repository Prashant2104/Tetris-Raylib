#pragma once
#include "Position.h"

namespace Settings {
	//Window Settings
	inline constexpr int screenWidth = 625;
	inline constexpr int screenHeight = 720;
	inline constexpr int fps = 60;
	inline constexpr char* title = "Tetris";
	inline constexpr char* iconPath = "resources/Icons/tetris.png";

	//Board Settings
	inline constexpr int cellSize = 30;
	inline constexpr int padding = 1;

	inline constexpr int boardSizeX = 10;
	inline constexpr int boardSizeY = 20;

	inline constexpr int boardOffsetX = 50;
	inline constexpr int boardOffsetY = 50;

	//Tetromino Settings
	inline constexpr int fallTime = 1;
	inline constexpr int fallSpeed = 1;
}