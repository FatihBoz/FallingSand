#pragma once

#include "MovementBehaviour.h"

class FallingMovement : public MovementBehaviour
{
public:
	bool tryMove(Grid& grid, int x, int y) override;
};