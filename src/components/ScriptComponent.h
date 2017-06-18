#pragma once

#include "Component.h"

#include <LuaBridge.h>
extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include "../entity/AStar.h"

namespace Entity
{
	class Entity;
}

namespace Components
{
	class LuaPathFind
	{
	public:
		LuaPathFind()
		    : m_nextStepX(0)
		    , m_nextStepY(0)
			, m_pathSize(0)
		{
		}

		void updatePath(float x, float y, float tx, float ty);
		
		float getNextX() const { return  m_nextStepX; }
		float getNextY() const { return  m_nextStepY; }
		float getPathSize() const { return  m_pathSize; }

	private:
		float m_nextStepX, m_nextStepY, m_pathSize;
		std::vector<AStar::Location> m_path;
	};

	class LuaEntityHandle 
	{
	public:
		LuaEntityHandle(Entity::Entity* e)
			: e(e)
		{}

		// Lua bindings
		bool isMoving() const;
		void setMoving(bool moving) const;
		void setAnimation(const std::string& name) const;
		void setVelocity(float x, float y) const;
		void setSpriteFlip(bool flipped) const;
		float getX() const;
		float getY() const;
		LuaEntityHandle getPlayer() const;
		LuaPathFind getPathFind() const;

	private:
		Entity::Entity* e;
	};

	class ScriptComponent : public Component
	{
	public:
		luabridge::lua_State* LuaState;

		ScriptComponent(nlohmann::json json);

		std::unique_ptr<Component> clone() override { return std::make_unique<ScriptComponent>(*this); }

		static const uint ID = ComponentID::Script;
	};
}
