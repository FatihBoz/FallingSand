#include "FallingMovement.h"

bool FallingMovement::tryMove(Grid& grid, int x, int y)
{
	//right below check
	if (grid.trySwap(x, y, x, y + 1)) return true;

	//down right check
	if (grid.trySwap(x, y, x + 1, y + 1)) return true;

	//down left check
	if (grid.trySwap(x, y, x - 1, y + 1)) return true;

	//if cant move, return false
	return false;
}