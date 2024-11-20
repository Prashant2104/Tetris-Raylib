#include "Block.h"
#include "Settings.h"

Block::Block()
{
	cellSize = Settings::cellSize;
	rotationState = Rotation::UP;
	colors = GetAllCellColors();

	rowOffset = columnOffset = 0;
}

void Block::Draw(int offsetX, int offsetY)
{
	std::vector<Position> tiles = GetCellPositions();
	for (Position item : tiles) {
		//DrawRectangle(item.column * cellSize + offsetX, item.row * cellSize + offsetY, cellSize - 1, cellSize - 1, colors[id]);
		//DrawRectangleGradientH(item.column * cellSize + offsetX, item.row * cellSize + offsetY, cellSize - 1, cellSize - 1, RAYWHITE, colors[id]);
		DrawRectangleGradientEx(Rectangle{ (float)item.column * cellSize + offsetX, (float)item.row * cellSize + offsetY, (float)cellSize - 1, (float)cellSize - 1 },
			RAYWHITE, colors[id], colors[id], colors[id]);
	}
}

void Block::Move(int rows, int cols)
{
	rowOffset += rows;
	columnOffset += cols;
}

void Block::Rotate()
{
	if(id != 4)
		rotationState = Rotation((int(rotationState) + 1) % 4);
}

void Block::UndoRotate()
{
	if (id != 4)
		rotationState = Rotation((int(rotationState) + 3) % 4);
}

std::vector<Position> Block::GetCellPositions()
{
	std::vector<Position> tiles = cells[(int)rotationState];
	std::vector<Position> movedTiles;

	for (Position item : tiles) {
		Position newPos = Position(item.row + rowOffset, item.column + columnOffset);
		movedTiles.push_back(newPos);
	}
	return movedTiles;
}

void Block::ResetPos()
{
	rowOffset = columnOffset = 0;
	rotationState = Rotation::UP;
	switch (id)
	{
	case 3:
		Move(-1, 3);
		break;
	case 4:
		Move(0, 4);
		break;
	default:
		Move(0, 3);
		break;
	}
}
