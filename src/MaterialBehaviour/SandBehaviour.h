#pragma once

#include "MaterialBehaviour.h"
#include "FallingMovement.h"

class SandBehaviour : public MaterialBehaviour
{
private:
	FallingMovement movement;

public:
	void update(Grid& grid, int x, int y) override;
	
};