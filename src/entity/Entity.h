#pragma once

#include "../util/Types.h"

#include "component/Component.h"

#include <memory>
#include <unordered_map>

struct Timestep;

namespace Framework
{
	class Entity
	{
	private:
		uint64 m_ID;
		std::unordered_map<ComponentType*, std::unique_ptr<Component>> m_components;
	public:
		Entity();
		Entity(sf::Vector2f& position, sf::Sprite& sprite);

		void addComponent(std::unique_ptr<Component> component);

		virtual void update(const Timestep& ts) {};

		template<typename T>
		const T* getComponent() const
		{
			return getComponentInternal<T>().get();
		}

		template<typename T>
		T* getComponent()
		{
			return (T*)getComponentInternal<T>().get();
		}
	private:
		template <typename T>
		const std::unique_ptr<Component>& getComponentInternal() const
		{
			ComponentType* type = T::getStaticType();
			std::unordered_map<ComponentType*, std::unique_ptr<Component>>::const_iterator it = m_components.find(type);
			if (it == m_components.end())
				return nullptr;
			return it->second;
		}
	};
}
