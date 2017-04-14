#pragma once

#include "Types.h"
#include "../level/Level.h"

#include <SFML/Graphics.hpp>

namespace Util
{
	typedef sf::Vector2<int32> Vec2i;

	struct Node
	{
		Node* parent;
		Vec2i pos;

		double fCost;
		double hCost;
		double gCost;

		Node(Vec2i pos, Node* parent, double gCost, double hCost)
		: parent(parent)
		, pos(pos)
		, fCost(gCost + hCost)
		, hCost(hCost)
		, gCost(gCost)
		{
		}
	};

	double distance(const Vec2i& v1, const Vec2i& v2);
    bool vecInList(std::vector<Node*> list, const Vec2i& vec);

	std::vector<Node*> AStar(Vec2i start, Vec2i end, Level::Level* level);
}
