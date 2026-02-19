#pragma once
#include "InteractionTable.h"
#include "MaterialBehaviour.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>


// y * columns + x
using CellIndex = int;

struct Cell
{
    int x;
    int y;
    int id = 0;
};

struct GridInfo
{
    int rows;
    int columns;
    int* grid;

    inline int& getValue(int x, int y)
    {
        return grid[y * columns + x];
	}
};

class Grid
{
private:
	InteractionTable interactionTable;
    std::vector<bool> isActive;
    std::vector<CellIndex> activeCells;
    std::vector<int> gridArr;
    int rows;
    int columns;

public:
    Grid(int rowCount, int columnCount);

    int& getValue(int x, int y);

    void setValue(int x, int y, int value);

    void addCell(int x, int y, int value);

    void update(std::vector<std::unique_ptr<MaterialBehaviour>>& behaviours);

    void drawGrid(sf::RenderWindow& window, int cellSize);

    bool trySwap(int x1, int y1, int x2, int y2);

    int checkForInteraction(int index1, int index2);

    void markActive(int index);

    int getRows() const { return rows; }

    int getColumns() const { return columns; }
};
