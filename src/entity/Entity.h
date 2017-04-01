#pragma once

#include "../util/Types.h"

#include <SFML/Graphics.hpp>

namespace entity
{
	// Knowing the damage source WILL be useful later if there are stats, buffs
	// or potions reducing specific types of dmg. (eg. Fire Resist or Magic Resist)
	//
	// (True damage ignores defences.)
	enum class DamageSource : byte
	{
		Fire    = 0,
		Magic   = 1,
		True    = 2
	};

	// Damage struct holding some data about damage instances.
	struct Damage
	{
		DamageSource source;
		int32 amount;
	};

	class Entity
	{
	public:
		Entity(float width, float height);

		// Default entity doesn't care about damage sources. (He just takes it)
		// Later other entites (eg: Player) will care tho. Since they will have stats and buffs
		///@TODO Better method name
		virtual void damage(Damage damage);
		int32 getHealth();

		void render(sf::RenderWindow& window);

		// Returns entity's shape. Use to apply transormations.
		sf::RectangleShape& getShape();
	private:
		int32 m_health;

		sf::RectangleShape m_shape;
	public:
		///@TODO Public for now. Change later
		sf::Vector2<float> velocity;
	};
}
