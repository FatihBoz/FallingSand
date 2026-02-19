#include "Grid.h"
#include "MaterialBehaviour.h"

Grid::Grid(int rowCount, int columnCount)
    : interactionTable(static_cast<int>(Material::COUNT)),
    isActive(),
    activeCells(),
    gridArr(rowCount* columnCount),
    rows(rowCount),
    columns(columnCount)
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
    for (int y = rows - 2; y >= 0; --y)
    {
        for (int x = 0; x < columns; ++x)
        {
            int index = y * columns + x;

            int value = gridArr[index];
            if (value == 0)
                continue;

            behaviours[value]->update(*this, x, y);
        }
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
            case 5:
                cell.setFillColor(sf::Color::Green);
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

        auto mat = checkForInteraction(gridArr[index1], gridArr[index2]);
        if (mat.result != -1) {

            if (mat.affectSource)
                gridArr[index1] = mat.result;

            else {
                gridArr[index2] = mat.result;
                gridArr[index1] = 0;
            }
        }

        return false;
    }


    std::swap(gridArr[index1], gridArr[index2]);

    return true;
}
InteractionResult Grid::checkForInteraction(int index1, int index2) {

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





