#pragma once
#include "Grid.h"

class MovementBehaviour
{
public:
	virtual bool tryMove(Grid& grid, int nx, int ny) = 0;
	virtual ~MovementBehaviour() = default;
};