#pragma once

#include "Component.h"
#include "../animation/Animator.h"

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
