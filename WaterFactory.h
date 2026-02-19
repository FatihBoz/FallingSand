#pragma once

#include "BehaviourFactory.h"
#include "WaterBehaviour.h"

class WaterFactory : public BehaviourFactory
{
public:
	std::unique_ptr<MaterialBehaviour> createBehaviour() override
	{
		return std::make_unique<WaterBehaviour>();
	}
};