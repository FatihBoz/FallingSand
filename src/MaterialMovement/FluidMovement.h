#pragma once

#include "MovementBehaviour.h"

class FluidMovement : public MovementBehaviour
{
public:
	bool tryMove(Grid& grid, int x, int y) override;
};