#include "WaterBehaviour.h"

void WaterBehaviour::update(Grid& grid, int x, int y)
{
	movement.tryMove(grid, x, y);
}