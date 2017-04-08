#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

namespace Framework
{
	struct ComponentType
	{
		std::string name;
	};

	class Component
	{
	public:
		Component() {};

		virtual ComponentType* getType() const { return nullptr; }
	};
}