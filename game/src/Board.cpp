#include "Board.h"
#include<assert.h>
Board::Cell::Cell() :
    bExists(false),
    color(WHITE)
{
}

void Board::Cell::SetColor(Color c)
{
    color = c;
    bExists = true;
}

void Board::Cell::Remove()
{
    bExists = false;
}

bool Board::Cell::Exists() const
{
    return bExists;
}

Color Board::Cell::GetColor() const
{
    return color;
}

Board::Board(Vec2<int> screenPos, Vec2<int> boardSize, int cellSize, int padding) :
    screenPos(screenPos),
    boardSize(boardSize),
    cellSize(cellSize),
    padding(padding)
{
    assert(boardSize.GetX() > 0 && boardSize.GetY() > 0);
    assert(cellSize > 0);
    cells.resize(boardSize.GetX() * boardSize.GetY());
}

void Board::SetCell(Vec2<int> pos, Color c)
{
    assert(pos.GetX() >= 0 && pos.GetY() >= 0 && pos.GetX() < boardSize.GetX() && pos.GetY() < boardSize.GetY());
    cells[pos.GetY() * boardSize.GetX() + pos.GetX()].SetColor(c);
}

void Board::DrawCell(Vec2<int> pos) const
{
    DrawCell(pos, cells[pos.GetY() * boardSize.GetX() + pos.GetX()].GetColor());
}

void Board::DrawCell(Vec2<int> pos, Color color) const
{
    assert(pos.GetX() >= 0 && pos.GetY() >= 0 && pos.GetX() < boardSize.GetX() && pos.GetY() < boardSize.GetY());
    Vec2<int> topLeft = screenPos + padding + (pos * cellSize);
    raycpp::DrawRectangle(topLeft, Vec2<int>{ cellSize, cellSize} - padding, color);
}

void Board::DrawBorder() const
{
    raycpp::DrawRectangleLinesEx(screenPos - (cellSize / 2), (boardSize * cellSize) + cellSize + padding, cellSize / 2, BLACK);
}

void Board::Draw() const
{
    for (int i = 0; i < boardSize.GetY(); i++) {
        for (int j = 0; j < boardSize.GetX(); j++) {
            if (CellExists({ j, i })) {
                DrawCell({ j, i });
            }
        }
    }
    DrawBorder();
}

bool Board::CellExists(Vec2<int> pos) const
{
    return cells[pos.GetY() * boardSize.GetX() + pos.GetX()].Exists();
}

Vec2<int> Board::GetBoardSize() const
{
    return boardSize;
}
