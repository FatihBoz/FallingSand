#pragma once

#include "MovementBehaviour.h"

class StaticMovement : public MovementBehaviour
{
public:
	bool tryMove(Grid& grid, int x, int y) override
	{
		return false;
	}
};