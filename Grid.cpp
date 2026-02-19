#include "Grid.h"
#include "MaterialBehaviour.h"

Grid::Grid(int rowCount, int columnCount) : rows(rowCount), columns(columnCount), gridArr(rowCount* columnCount), interactionTable(static_cast<int>(Material::COUNT))
{
    // to prevent fps drops while doubling the array size in much bigger scale.
    activeCells.reserve(rowCount * columnCount);
	isActive.resize(rowCount * columnCount, false);
}

int& Grid::getValue(int x, int y)
{
    return gridArr[y * columns + x];
}

void Grid::setValue(int x, int y, int value)
{
    gridArr[y * columns + x] = value;
}


void Grid::addCell(int x, int y, int value) {
    activeCells.push_back(y * columns + x);
    getValue(x, y) = value;
}
 

void Grid::update(std::vector<std::unique_ptr<MaterialBehaviour>>& behaviours)
{
	//Iterating backwards to avoid issues with activeCells being modified during iteration
    for (int i = static_cast<int>(activeCells.size()) - 1; i >= 0; --i)
    {
        int index = activeCells[i];

        if (gridArr[index] == 0) continue;

        int value = gridArr[index];
        int x = index % columns;
        int y = index / columns;

        behaviours[value]->update(*this, x, y);
    }
}



void Grid::drawGrid(sf::RenderWindow& window, int CELL_SIZE)
{
    sf::RectangleShape cell(   
        sf::Vector2f(CELL_SIZE, CELL_SIZE)
    );

    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < columns; x++)
        {
            int value = getValue(x, y);
            
            switch (value)
            {
            case 0:
                cell.setFillColor(sf::Color::Black);
				break;
            case 1:
                cell.setFillColor(sf::Color::Yellow);
				break;
            case 2:
				cell.setFillColor(sf::Color::Blue);
                break;
            case 3:
                cell.setFillColor(sf::Color::White);
				break;
            case 4:
                cell.setFillColor(sf::Color::Red);
				break;

            default:
                break;
            };
            
            sf::Vector2f tempVector = sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE);
            
            cell.setPosition(tempVector);

            window.draw(cell);
            
        }
    }
}

bool Grid::trySwap(int x1, int y1, int x2, int y2) {

    if (x2 < 0 || x2 >= columns || y2 < 0 || y2 >= rows)
        return false;

    int index1 = y1 * columns + x1;
    int index2 = y2 * columns + x2;

    if (gridArr[index2] != 0) {

        int mat = checkForInteraction(gridArr[index1], gridArr[index2]);
        if (mat != -1) {
            // interaction: write result to destination, clear source
            gridArr[index2] = mat;
            gridArr[index1] = 0;

            markActive(index2);
        }

        return false;
    }


    std::swap(gridArr[index1], gridArr[index2]);
    markActive(index2);

    return true;
}
int Grid::checkForInteraction(int index1, int index2) {

    return interactionTable.getInteraction(index1, index2);
}


void Grid::markActive(int index)
{
    if (gridArr[index] == 0)
        return;

    //if index is not in activeCells, add
    if (!isActive[index])
    {
		isActive[index] = true;
        activeCells.push_back(index);
    }
}





