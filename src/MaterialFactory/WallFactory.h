#pragma once

#include "BehaviourFactory.h"
#include "WallBehaviour.h"

class WallFactory : public BehaviourFactory
{
public:
	std::unique_ptr<MaterialBehaviour> createBehaviour() override
	{
		return std::make_unique<WallBehaviour>();
	}
};
