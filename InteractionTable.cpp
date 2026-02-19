#include "InteractionTable.h"


InteractionTable::InteractionTable(int count)
    : table(count, std::vector<InteractionResult>(count, InteractionResult{ -1, false })) {
	int matCount = static_cast<int>(Material::COUNT);
	int lavaIndex = static_cast<int>(Material::LAVA);
	int waterIndex = static_cast<int>(Material::WATER);
	int plantIndex = static_cast<int>(Material::PLANT);


	//LAVA
	for (int i = 0; i < matCount; ++i) {
		if (lavaIndex == i) continue;
		//Lava destroys everything it interacts with except for itself
		table[lavaIndex][i] = { lavaIndex, false };
		table[i][lavaIndex] = { lavaIndex,false };
	}

	//Lava + Water = Wall
	table[lavaIndex][waterIndex] = { static_cast<int>(Material::WALL) , false};
	table[waterIndex][lavaIndex] = { static_cast<int>(Material::WALL) , false };

	//Water + Plant = 2 x Plant  also keep source
	table[waterIndex][plantIndex] = { plantIndex,true };
	table[plantIndex][waterIndex] = { plantIndex,true };

}


InteractionResult InteractionTable::getInteraction(int r, int c) {

	if (r < 0 || r >= static_cast<int>(table.size()) || c < 0 || c >= static_cast<int>(table[r].size()))
		return { -1, false };

	return table[r][c];
}

InteractionResult InteractionTable::getInteraction(Material m1, Material m2) {
	int r = static_cast<int>(m1);
	int c = static_cast<int>(m2);

	if (r < 0 || r >= static_cast<int>(table.size()) || c < 0 || c >= static_cast<int>(table[r].size()))
		return {-1, false};

	return table[r][c];
}