#pragma once

#include "../level/Level.h"
#include "../maths/Maths.h"

#include <SFML/Graphics.hpp>

namespace Util
{
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

    bool vecInList(std::vector<Node*> list, const Vec2i& vec);

	std::vector<Node*> AStar(Vec2i start, Vec2i end, Level::Level* level);
}
