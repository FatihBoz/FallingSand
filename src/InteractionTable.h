#pragma once
#include "Material.h"
#include <vector>

struct InteractionResult {
	int result;
	bool affectSource;
};

class InteractionTable {
private:
	std::vector<std::vector<InteractionResult>> table;

public:
	InteractionTable(int count);
	InteractionResult getInteraction(int a, int b);
	InteractionResult getInteraction(Material m1, Material m2);
};