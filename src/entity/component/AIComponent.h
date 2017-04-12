#pragma once

#include <functional>

#include "Component.h"

namespace Framework
{
	class Entity;

	class AIComponent : public Component
	{
	public:
		std::function<void(Entity* entity)> ai;
	public:
		AIComponent(std::function<void(Entity* entity)> ai);

		static ComponentType* getStaticType();
		virtual ComponentType* getType() const override;;
	};
}