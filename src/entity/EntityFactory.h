#pragma once

#include "Entity.h"

namespace Entity
{
	class EntityFactory 
	{
    public:
        static std::unique_ptr<Entity> createEntity(std::string filePath);
    };
}
