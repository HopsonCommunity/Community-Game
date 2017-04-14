#pragma once

#include <SFML/System/Vector2.hpp>

#include "Component.h"

#include "../physics/Hitbox.h"
#include "../../util/json.hpp"

namespace Framework
{
	class CollisionComponent : public Component
	 {
	public:
		Hitbox aabb;
	public:
		CollisionComponent(const Hitbox& hitbox);
		CollisionComponent(nlohmann::json json);

		static ComponentType* getStaticType();
		virtual ComponentType* getType() const override;;
	};
}
