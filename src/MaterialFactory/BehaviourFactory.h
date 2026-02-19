#pragma once

#include <memory>
#include "MaterialBehaviour.h"

class BehaviourFactory
{
public:
    virtual std::unique_ptr<MaterialBehaviour> createBehaviour() = 0;
    virtual ~BehaviourFactory() = default;
};
