#include "SandBehaviour.h"

void SandBehaviour::update(Grid& grid, int x, int y)
{
	movement.tryMove(grid, x, y);
}
	