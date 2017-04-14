#pragma once

#include "Entity.h"

#include "../util/json.hpp"

namespace Framework 
{
	class EntityFactory 
	{
    public:
        static std::unique_ptr<Entity> createEntity(std::string filePath);
    };
}
