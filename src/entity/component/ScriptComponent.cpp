#include "ScriptComponent.h"

#include "Components.h"
#include "../Entity.h"

#include "../../util/Log.h"
#include "../../maths/AStar.h"
#include "../../app/Application.h"
#include "../../app/states/StatePlaying.h"

#define ADD_Application_FUNCTION(x) addFunction(#x, &Application::x)
#define ADD_LuaPathFind_FUNCTION(x) addFunction(#x, &LuaPathFind::x)
#define ADD_LuaEntityHandle_FUNCTION(x) addFunction(#x, &LuaEntityHandle::x)

namespace Entity
{
	void LuaPathFind::updatePath(float x, float y, float tx, float ty)
	{
		m_path.clear();
		m_path = AStar::constructPath(
			std::forward_as_tuple(static_cast<int32>(x / TILE_SIZE), static_cast<int32>(y / TILE_SIZE)),
			std::forward_as_tuple(static_cast<int32>(tx / TILE_SIZE), static_cast<int32>(ty / TILE_SIZE))
		);
		if (!m_path.empty())
		{
			AStar::Location loc = m_path[m_path.size() - 1];
			m_nextStepX = std::get<0>(loc) * TILE_SIZE;
			m_nextStepY = std::get<1>(loc) * TILE_SIZE;
			m_pathSize = m_path.size();
		}
	}

	bool LuaEntityHandle::isMoving() const
	{
		PhysicsComponent* c_phys = e->getComponent<PhysicsComponent>();
		if (c_phys)
			return c_phys->moving;
		return false;
	}

	void LuaEntityHandle::setMoving(bool moving) const
	{
		PhysicsComponent* c_phys = e->getComponent<PhysicsComponent>();
		if (c_phys)
			c_phys->moving = moving;
	}

	void LuaEntityHandle::setAnimation(const std::string& name) const
	{
		SpriteComponent* c_sprite = e->getComponent<SpriteComponent>();
		if (c_sprite && c_sprite->animated)
			c_sprite->animator.setAnimation(name);
	}

	void LuaEntityHandle::setVelocity(float x, float y) const
	{
		PhysicsComponent* c_phys = e->getComponent<PhysicsComponent>();
		if (c_phys)
			c_phys->setVelocity(x, y);
	}

	void LuaEntityHandle::setSpriteFlip(bool flipped) const
	{
		SpriteComponent* c_sprite = e->getComponent<SpriteComponent>();
		if (c_sprite)
			c_sprite->flipX = flipped;
	}

	float LuaEntityHandle::getX() const
	{
		PhysicsComponent* c_phys = e->getComponent<PhysicsComponent>();
		if (c_phys)
			return c_phys->pos.x;
		return 0;
	}

	float LuaEntityHandle::getY() const
	{
		PhysicsComponent* c_phys = e->getComponent<PhysicsComponent>();
		if (c_phys)
			return c_phys->pos.y;
		return 0;
	}

	LuaEntityHandle LuaEntityHandle::getPlayer() const
	{
		return LuaEntityHandle(State::Playing::instance->getLevel().player);
	}

	LuaPathFind LuaEntityHandle::getPathFind() const
	{
		return LuaPathFind();
	}

	ScriptComponent::ScriptComponent(nlohmann::json json)
	{
		std::string path = "$$path";

		if (json.find("src") == json.end())
			LOG_ERROR("[JSON] Entity with ScriptComponent but no script source!");
		else
			path = json["src"].get<std::string>();

		LuaState = luabridge::luaL_newstate();
		luaL_openlibs(LuaState);
		getGlobalNamespace(LuaState)
			.beginClass<Application>("Application")
			.addFunction("keyPressed", &Application::inputPressed)
			.ADD_Application_FUNCTION(mouseX)
			.ADD_Application_FUNCTION(mouseY)
			.ADD_Application_FUNCTION(screenWidth)
			.ADD_Application_FUNCTION(screenHeight)
			.endClass()
			.beginClass<LuaPathFind>("LuaPathFind")
			.ADD_LuaPathFind_FUNCTION(updatePath)
			.ADD_LuaPathFind_FUNCTION(getNextX)
			.ADD_LuaPathFind_FUNCTION(getNextY)
			.ADD_LuaPathFind_FUNCTION(getPathSize)
			.endClass()
			.beginClass<LuaEntityHandle>("LuaEntityHandle")
			.ADD_LuaEntityHandle_FUNCTION(setAnimation)
			.ADD_LuaEntityHandle_FUNCTION(setVelocity)
			.ADD_LuaEntityHandle_FUNCTION(isMoving)
			.ADD_LuaEntityHandle_FUNCTION(setMoving)
			.ADD_LuaEntityHandle_FUNCTION(setSpriteFlip)
			.ADD_LuaEntityHandle_FUNCTION(getX)
			.ADD_LuaEntityHandle_FUNCTION(getY)
			.ADD_LuaEntityHandle_FUNCTION(getPlayer)
			.ADD_LuaEntityHandle_FUNCTION(getPathFind)
			.endClass();

		luaL_dofile(LuaState, std::string("res/scripts/" + path).c_str());
		lua_pcall(LuaState, 0, 0, 0);
	}
}
