#pragma once

#include <SFML/Graphics.hpp>
#include "../util/FileUtil.h"
#include "../util/json.hpp"
#include "../util/Types.h"

namespace Input 
{
	class InputScheme
	{
	public:
		InputScheme(std::string fileName);

		sf::Keyboard::Key getKeyForAction(std::string actionName);
	private:
		void initMap();

		std::map<std::string, sf::Keyboard::Key> m_nameMap;
		std::map<std::string, sf::Keyboard::Key> m_actionMap;
	};
}