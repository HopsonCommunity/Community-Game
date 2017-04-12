#pragma once

#include "../../../util/Types.h"
#include "../../../level/Level.h"

#include <SFML/Graphics.hpp>

namespace Framework
{
	typedef sf::Vector2<int32> Vec2i;

	struct Node
	{
		Node* parent;
		Vec2i pos;
		
		double fCost, gCost, hCost;

		Node(Vec2i pos, Node* parent, double gCost, double hCost)
		: parent(parent), pos(pos), fCost(gCost + hCost), hCost(hCost), gCost(gCost)
		{
		}
	};

	class AStar
	{
		private:
			static double distance(const Vec2i& v1, const Vec2i& v2);
			static bool vecInList(std::vector<Node*> list, const Vec2i& vec);
	
		public:
			static std::vector<Node*> findPath(Vec2i start, Vec2i end, Level::Level* level);
	};
}