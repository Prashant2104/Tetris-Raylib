#pragma once
#include<vector>
#include"raylib.h"
#include"Settings.h"
class Board
{
public:
	Board();
	void Initialize();
	void Draw();
	bool IsCellOutside(int row, int col);
	bool IsCellEmpty(int row, int col);
	int ClearFullRows();
	int grid[Settings::boardSizeY][Settings::boardSizeX];
private:
	int numRows, numCols;
	int boardOffsetX, boardOffsetY;
	int cellSize;
	int padding;
	std::vector<Color> colors;
	bool IsRowFull(int row);
	void ClearRow(int row);
	void MoveRowDown(int row, int numRows);
};

