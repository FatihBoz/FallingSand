#pragma once
#include "BehaviourFactory.h"
#include "LavaBehaviour.h"

class LavaFactory : public BehaviourFactory
{
public:
	std::unique_ptr<MaterialBehaviour> createBehaviour() override
	{
		return std::make_unique<LavaBehaviour>();
	}
};