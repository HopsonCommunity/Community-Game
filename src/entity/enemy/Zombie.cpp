#include "Zombie.h"

#include "../../Application.h"

namespace Framework
{
	Zombie::Zombie(const sf::Vector2f& position)
	: Entity(sf::Vector2f(position.x, position.y), sf::Sprite(Application::instance->getResources().textures.get("player_modelDefault"), sf::IntRect(0, 0, 32, 64)))
	{

	}
}
