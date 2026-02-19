#pragma once
class Grid;

class MaterialBehaviour
{
public:
	virtual void update(Grid& grid, int x, int y) = 0;
	virtual ~MaterialBehaviour() = default;
};