#include "WallBehaviour.h"

void WallBehaviour::update(Grid& grid, int x, int y)
{
	movement.tryMove(grid, x, y);
}