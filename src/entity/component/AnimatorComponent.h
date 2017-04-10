#pragma once

#include "../animation/Animator.h"

#include "Component.h"

namespace Framework
{
	class AnimatorComponent : public Component
	{
	public:
		Animator animator;
	public:
		AnimatorComponent(Animator animator);

		static ComponentType* getStaticType();
		virtual ComponentType* getType() const override;;
	};
}