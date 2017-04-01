#pragma once

#include <string>

namespace entity {
	
	struct ComponentType
	{
		std::string name;
	};

	class Component
	{
	public:
		Component();
		virtual ~Component();

		virtual ComponentType* GetType() const { return nullptr; }
	};
}