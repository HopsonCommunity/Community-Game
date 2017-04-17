#pragma once

#include "Entity.h"

#include <vector>

namespace Entity
{
	class EntityFactory 
	{
    public:
        EntityFactory();
        std::unique_ptr<Entity> createEntity(std::string name);
        std::unique_ptr<Entity> createHostileEntity();
    private:
        void createTemplate(std::string filePath);

        std::unordered_map<std::string, std::unique_ptr<Entity>> m_templates;
        uint64 m_lastID;

        std::vector<std::string> m_hostileMobs;
    };
}
