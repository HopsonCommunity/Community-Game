#pragma once

#include "../util/Types.h"

#include "component/Component.h"

#include <unordered_map>

struct Timestep;

namespace Framework
{
	class Entity
	{
	private:
		uint64 m_ID;
		std::unordered_map<ComponentType*, Component*> m_components;
	public:
		Entity();
		Entity(sf::Vector2f& position, sf::Sprite& sprite);

		void addComponent(Component* component);

		virtual void update(const Timestep& ts) {};

		template<typename T>
		const T* getComponent() const
		{
			return getComponentInternal<T>();
		}

		template<typename T>
		T* getComponent()
		{
			return (T*)getComponentInternal<T>();
		}
	private:
		template <typename T>
		const T* getComponentInternal() const
		{
			ComponentType* type = T::getStaticType();
			auto it = m_components.find(type);
			if (it == m_components.end())
				return nullptr;
			return (T*)it->second;
		}
	};
}
