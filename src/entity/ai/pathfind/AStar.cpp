#include "AStar.h"
#include <math.h>

namespace Framework
{
	double AStar::distance(const Vec2i& v1, const Vec2i& v2)
	{
		double dx = v1.x - v2.x;
		double dy = v1.y - v2.y;
		return sqrt(dx * dx + dy * dy);
	}

	bool AStar::vecInList(std::vector<Node*> list, const Vec2i& vec)
	{
		for (int i = 0; i < list.size(); i++)
			if (list[i]->pos.x == vec.x && list[i]->pos.y == vec.y) return true;

		return false;
	}

	//
	// Attention pls. I'm aware there is a high probability of memory leak somewhere here. If you find it, fix it.
	// (I'm too lazy to do it :/)
	//
	std::vector<Node*> AStar::findPath(Vec2i start, Vec2i end, Level::Level* level)
	{
		std::vector<Node*> path;

		std::vector<Node*> openList;
		std::vector<Node*> closedList;
		double dist = distance(start, end);
		Node* current = new Node(start, nullptr, 0, dist);
		openList.push_back(current);
		while (openList.size() > 0)
		{
			std::sort(openList.begin(), openList.end(),
				[](Node* lhs, Node* rhs) {
				return lhs->fCost < rhs->fCost;
			});

			current = openList[0];
			if (current->pos == end)
			{
				while (current->parent)
				{
					path.push_back(current);
					current = current->parent;
				}
				return path;
			}
			openList.erase(std::remove(openList.begin(), openList.end(), current), openList.end());
			closedList.push_back(current);

			for (uint i = 0; i < 9; ++i)
			{
				if (i == 4)
					continue;

				int32 x = current->pos.x;
				int32 y = current->pos.y;
				int32 xi = (i % 3) - 1;
				int32 yi = (i / 3) - 1;

				Level::Tile::Tile* at = level->getTile(x + xi, y + yi);
				if (!at)
					continue;
				//if (at->isSolid())
				//	continue;

				Vec2i a = { x + xi, y + yi };
				double gCost = current->gCost + (distance(current->pos, a) == 1 ? 1 : 2);
				double hCost = distance(a, end);
				Node* node = new Node(a, current, gCost, hCost);
				if (vecInList(closedList, a) && gCost >= node->gCost)
					continue;
				if (!vecInList(openList, a) || gCost < node->gCost)
					openList.push_back(node);
			}
		}
		return path;
	}
}
