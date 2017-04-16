#pragma once

#include "../Entity.h"

#include <vector>

struct Timestep;

namespace Entity
{
	class System
	{
	public:
		virtual void update(const Timestep& ts, Entity* entity) {};
	};

	class MoveSystem : public System
	{
	public:
		void update(const Timestep& ts, Entity* entity) override;
	}; 

	class StatsSystem : public System
	{
	public:
		void update(const Timestep& ts, Entity* entity) override;
	};

	class AnimatorSystem : public System
	{
		void update(const Timestep& ts, Entity* entity) override;
	};

	class RenderSystem : public System
	{
	public:
		void update(const Timestep& ts, Entity* entity) override;
	};

    class AISystem : public System
    {
    public:
        void update(const Timestep& ts, Entity* entity) override;
    };

    class PlayerInputSystem : public System
    {
    public:
        void update(const Timestep& ts, Entity* entity) override;
    };
}
