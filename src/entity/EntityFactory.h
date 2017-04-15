#pragma once

#include "Entity.h"

namespace Framework 
{
	class EntityFactory 
	{
    public:
        static std::unique_ptr<Entity> createEntity(std::string filePath);
    };
}
