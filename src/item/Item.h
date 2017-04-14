#pragma once

#include "../util/Types.h"
#include <memory>
#include <unordered_map>

#include "component/Component.h"
#include "../entity/Entity.h"

namespace Item
{
    class Item
    {
    public:
        Item(Framework::Entity* owningEntity);

        void addComponent(std::unique_ptr<Component> component);

        template<typename T>
        const T* getComponent() const
        {
            return getComponentInternal<T>().get();
        }

        template<typename T>
        T* getComponent()
        {
            return (T*)getComponentInternal<T>();
        }

        uint64 getID() { return m_ID; }

        void changeOwningEntity(Framework::Entity* entity) 
        {
            m_owningEntity = entity;
        }

        Framework::Entity* getOwningEntity()
        {
            return m_owningEntity;
        }

    private:
        template <typename T>
        const Component* getComponentInternal() const
        {
            ComponentType* type = T::getStaticType();
            auto it = m_components.find(type);
            if (it == m_components.end())
                return nullptr;
            return it->second.get();
        }

        uint64 m_ID;
        std::unordered_map<ComponentType*, std::unique_ptr<Component>> m_components;
        Framework::Entity* m_owningEntity;
    };
}