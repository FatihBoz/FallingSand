#include "LavaBehaviour.h"

void LavaBehaviour::update(Grid& grid, int x, int y)
{
	//if (y + 1 < grid.getRows() && grid.getValue(x, y + 1) != 0) {
	//	//Lava destroys both itself and the material below it
	//	grid.setValue(x, y, 0);
	//	grid.setValue(x, y + 1, 0);
	//	return;
	//}
	
	//if below is empty, try to move
	if (movement.tryMove(grid, x, y))
		return;
}