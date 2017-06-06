#pragma once

#include "../entity/Entity.h"
#include "../components/Component.h"

namespace Item
{
    class Item
    {
    public:
        Item();
        Item(Entity::Entity* owningEntity, uint64 ID);

        uint64 getID() { return m_ID; }

        template<typename T>
        void addComponent(std::unique_ptr<Entity::Component> component)
        {
            m_components[int(T::ID)] = std::move(component);
        }

        template<typename T>
        T* getComponent()
        {
            int id = int(T::ID);
            auto it = m_components.find(id);
            if (it == m_components.end())
                return nullptr;
            else
                return dynamic_cast<T*>(it->second.get());
        }

        void changeOwningEntity(Entity::Entity* entity)
        {
            m_owningEntity = entity;
        }

        Entity::Entity* getOwningEntity()
        {
            return m_owningEntity;
        }

        std::unique_ptr<Item> clone(uint64 id);

    private:
        uint64 m_ID;
        std::unordered_map<int, std::unique_ptr<Entity::Component>> m_components;
        Entity::Entity* m_owningEntity;
    };
}
