#pragma once

#include "Component.h"

#include "../animation/Animator.h"
#include "../../util/json.hpp"

namespace Entity
{
	class AnimatorComponent : public Component
	{
    public:
		Animator animator;

		AnimatorComponent(Animator animator);
		AnimatorComponent(nlohmann::json json);

        static const int ID = 2;
	};
}
