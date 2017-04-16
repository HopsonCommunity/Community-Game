#pragma once

#include "Component.h"

#include "../physics/Hitbox.h"
#include "../../util/json.hpp"

namespace Entity
{
	class CollisionComponent : public Component
	{
    public:
		Hitbox aabb;

		CollisionComponent(const Hitbox& hitbox);
		CollisionComponent(nlohmann::json json);

        static const int ID = 3;
	};
}
