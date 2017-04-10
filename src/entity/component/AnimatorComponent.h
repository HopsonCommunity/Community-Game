#pragma once

#include "../animation/Animator.h"

#include "Component.h"
#include "../../util/json.hpp"

namespace Framework
{
	class AnimatorComponent : public Component
	{
	public:
		Animator animator;
	public:
		AnimatorComponent(Animator animator);
		AnimatorComponent(nlohmann::json json);

		static ComponentType* getStaticType();
		virtual ComponentType* getType() const override;;
	};
}
