#pragma once

#include "Component.h"

namespace Entity
{
	// Marks the entity as hostile
	class HostileComponent : public Component
	{
	public:
		HostileComponent();
		HostileComponent(nlohmann::json json);

		static const uint ID = ComponentID::Hostile;
	};
}