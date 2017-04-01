#include "Entity.h"

namespace entity {

	Entity::Entity(float width, float height)
		: m_shape({ width, height })
	{
	}

	void Entity::damage(Damage damage)
	{
		m_health -= damage.amount; 
	}
	
	int32 Entity::getHealth() 
	{
		return m_health; 
	}

	void Entity::render(sf::RenderWindow& window)
	{
		window.draw(m_shape);
	}

	sf::RectangleShape & Entity::getShape() 
	{
		return m_shape; 
	}
}