#pragma once
#include "BehaviourFactory.h"
#include "PlantBehaviour.h"

class PlantFactory : public BehaviourFactory
{
public:
	std::unique_ptr<MaterialBehaviour> createBehaviour() override
	{
		return std::make_unique<PlantBehaviour>();
	}
};