#pragma once

#include "../components/Component.h"

#include "../maths/maths.h"

struct Timestep;

namespace Entity
{
	class Entity
	{
	public:
		Entity();
		Entity(uint64 ID);

		uint64 getID() { return m_ID; }

		template<typename T>
		void addComponent(std::unique_ptr<Components::Component> component)
		{
			m_components[int(T::ID)] = std::move(component);
		}

		template<typename T>
		T* getComponent()
		{
			uint id = T::ID;
			auto it = m_components.find(id);
			if (it == m_components.end())
				return nullptr;
			return dynamic_cast<T*>(it->second.get());
		}

		std::unique_ptr<Entity> clone(uint64 id);
	private:
		uint64 m_ID;
		std::unordered_map<uint, std::unique_ptr<Components::Component>> m_components;
	};
}
