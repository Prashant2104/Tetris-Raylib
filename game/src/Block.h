#pragma once
#include<vector>
#include<map>
#include"Position.h"
#include"Colors.h"

class Block
{
public:
	enum class Rotation
	{
		UP,
		RIGHT,
		DOWN,
		LEFT
	};
	Block();
	void Draw(int offsetX, int offsetY);
	int id;
	std::map<int, std::vector<Position>> cells;
	void Move(int rows, int cols);
	void Rotate();
	void UndoRotate();
	std::vector<Position> GetCellPositions();
private:
	int cellSize;
	Rotation rotationState;
	std::vector<Color> colors;
	int rowOffset, columnOffset;
};
