#include "Board.h"
#include "Colors.h"

Board::Board()
{
	numRows = Settings::boardSizeY;
	numCols = Settings::boardSizeX;
	cellSize = Settings::cellSize;
	padding = Settings::padding;
	boardOffsetX = Settings::boardOffsetX;
	boardOffsetY = Settings::boardOffsetY;
	colors = GetAllCellColors();
	Initialize();
}

void Board::Initialize()
{
	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols; col++)
		{
			grid[row][col] = 0;
		}
	}
}

void Board::Draw()
{
	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols; col++)
		{
			int cellValue = grid[row][col];
			if(cellValue == 0)
				DrawRectangle(col * cellSize + boardOffsetX, row * cellSize + boardOffsetY, cellSize - padding, cellSize - padding, colors[cellValue]);
			else
				DrawRectangleGradientEx(Rectangle{ (float)col * cellSize + boardOffsetX, (float)row * cellSize + boardOffsetY, (float)cellSize - padding, (float)cellSize - padding },
					RAYWHITE, colors[cellValue], colors[cellValue], colors[cellValue]);
		}
	}
	//Kinda hard coded boundry
	DrawRectangle(boardOffsetX - 16, boardOffsetY + cellSize * numRows, numCols * cellSize + padding * cellSize + 1, 15, BLACK);
	DrawRectangle(boardOffsetX - 16, boardOffsetY, 15, numRows * cellSize + padding + 1, BLACK);
	DrawRectangle(boardOffsetX + cellSize * numCols, boardOffsetY, 15, numRows * cellSize + padding + 1, BLACK);
}

bool Board::IsCellOutside(int row, int col)
{
	if (row >= 0 && row < numRows && col >= 0 && col < numCols) {
		return false;
	}
	return true;
}

bool Board::IsCellEmpty(int row, int col)
{
	if (grid[row][col] == 0) {
		return true;
	}
	return false;
}

int Board::ClearFullRows()
{
	int completed = 0;
	for (int row = numRows - 1; row >= 0; row--)
	{
		if (IsRowFull(row))
		{
			ClearRow(row);
			completed++;
		}
		else if (completed > 0)
		{
			MoveRowDown(row, completed);
		}
	}
	return completed;
}

bool Board::IsRowFull(int row)
{
	for (int column = 0; column < numCols; column++)
	{
		if (grid[row][column] == 0)
		{
			return false;
		}
	}
	return true;
}

void Board::ClearRow(int row)
{
	for (int column = 0; column < numCols; column++)
	{
		grid[row][column] = 0;
	}
}

void Board::MoveRowDown(int row, int numRows)
{
	for (int column = 0; column < numCols; column++)
	{
		grid[row + numRows][column] = grid[row][column];
		grid[row][column] = 0;
	}
}