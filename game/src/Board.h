#pragma once
#include "RaylibCpp.h"
#include <vector>
#include "Vec2.h"

class Board {
private:
    class Cell {
    public:
        Cell();
        void SetColor(Color c);
        void Remove();
        bool Exists() const;
        Color GetColor() const;
    private:
        bool bExists;
        Color color;
    };
public:
    Board(Vec2<int> screenPos, Vec2<int> boardSize, int cellSize, int padding);
    void SetCell(Vec2<int> pos, Color c);
    void DrawCell(Vec2<int> pos) const;
    void DrawCell(Vec2<int> pos, Color color) const;
    void DrawBorder() const;
    void Draw() const;
    bool CellExists(Vec2<int> pos) const;
    Vec2<int> GetBoardSize() const;
private:
    std::vector<Cell> cells;
    const Vec2<int> boardSize;
    const int cellSize, padding;
    Vec2<int> screenPos;
};