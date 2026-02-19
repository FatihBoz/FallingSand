#pragma once
#include "BehaviourFactory.h"
#include "SandBehaviour.h"

class SandFactory : public BehaviourFactory
{
public:
	std::unique_ptr<MaterialBehaviour> createBehaviour() override
	{
		return std::make_unique<SandBehaviour>();
	}
};