#pragma once
#include "Material.h"
#include <vector>

class InteractionTable {
private:
	std::vector<std::vector<int>> table;

public:
	InteractionTable(int count);
	int getInteraction(int a, int b);
	int getInteraction(Material m1, Material m2);
};