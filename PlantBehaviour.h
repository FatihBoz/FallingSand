#pragma once
#include "MaterialBehaviour.h"
#include "StaticMovement.h"

class PlantBehaviour : public MaterialBehaviour
{
private:
	StaticMovement movement;
public:
	void update(Grid& grid, int x, int y) override;
};