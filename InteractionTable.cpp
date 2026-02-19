#include "InteractionTable.h"


InteractionTable::InteractionTable(int count) : table(count, std::vector<int>(count,-1)) {
	int matCount = static_cast<int>(Material::COUNT);
	int lavaIndex = static_cast<int>(Material::LAVA);


	//LAVA
	for (int i = 0; i < matCount; ++i) {
		if (lavaIndex == i) continue;
		//Lava destroys everything it interacts with except for itself
		table[lavaIndex][i] = static_cast<int>(Material::EMPTY);
	}

	//Lava + Water = Wall
	table[lavaIndex][static_cast<int>(Material::WATER)] = static_cast<int>(Material::WALL);

}


int InteractionTable::getInteraction(int r, int c) {

	if (r < 0 && r >= table.size() && c < 0 && c >= table[r].size())
		return -1;

	return table[r][c];
}

int InteractionTable::getInteraction(Material m1, Material m2) {
	int r = static_cast<int>(m1);
	int c = static_cast<int>(m2);

	if (r < 0 && r >= table.size() && c < 0 && c >= table[r].size())
		return -1;

	return table[r][c];
}