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
		DrawRectangle(item.column * cellSize + offsetX, item.row * cellSize + offsetY, cellSize - 1, cellSize - 1, colors[id]);
	}
}

void Block::Move(int rows, int cols)
{
	rowOffset += rows;
	columnOffset += cols;
}

void Block::Rotate()
{
	rotationState = Rotation((int(rotationState) + 1) % 4);
}

void Block::UndoRotate()
{
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
