#pragma once

#include "Entity.h"

namespace Entity
{
	class EntityFactory 
	{
    public:
        EntityFactory();
        std::unique_ptr<Entity> createEntity(std::string name);

    private:
        void createTemplate(std::string filePath);

        std::unordered_map<std::string, std::unique_ptr<Entity>> m_templates;
        uint64 m_lastID;
        
    };
}
