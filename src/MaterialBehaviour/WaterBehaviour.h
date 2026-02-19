#pragma once

#include "MaterialBehaviour.h"
#include "FluidMovement.h"


class WaterBehaviour : public MaterialBehaviour
{
private:
	FluidMovement movement;

public:
	void update(Grid& grid, int x, int y) override;
};