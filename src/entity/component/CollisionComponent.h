#pragma once

#include "Component.h"
#include "../physics/Hitbox.h"

namespace Entity
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
