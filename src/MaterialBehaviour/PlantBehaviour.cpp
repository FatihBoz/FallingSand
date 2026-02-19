#include "PlantBehaviour.h"

void PlantBehaviour::update(Grid& grid, int x, int y)
{
	//Plants don't move but they can interact with water to grow
	if (movement.tryMove(grid, x, y))
		return;
}
