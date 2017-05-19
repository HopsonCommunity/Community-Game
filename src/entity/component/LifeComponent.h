#pragma once

#include "Component.h"

namespace Entity
{
	class LifeComponent : public Component
	{
	public:
		float life;
		bool done = false;
	public:
		LifeComponent(float life);
		LifeComponent(nlohmann::json json);

		static const uint ID = ComponentID::Life;
	};
}
