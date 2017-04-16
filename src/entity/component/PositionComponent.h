#pragma once

#include "Component.h"

namespace Entity
{
	class PositionComponent : public Component
	{
	public:
		Vec2 position;
	public:
		PositionComponent(const Vec2& position = {0, 0});
		PositionComponent(nlohmann::json json);

		static ComponentType* getStaticType();
		virtual ComponentType* getType() const override;;
	};
}
