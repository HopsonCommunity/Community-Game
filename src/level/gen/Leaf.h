#pragma once

#include "../../Common.h"

#include "../../maths/maths.h"
#include "../../util/Random.h"

namespace WGenerator
{
	class Leaf
	{
	public:
		Leaf(IntRectangle t_block, std::shared_ptr<Random::Generator<> > t_generator, uint t_minSize, uint t_minHall, uint t_maxHall);

		bool split();
		void createRooms();

		std::shared_ptr<IntRectangle> room;
		IntRectangle block;

		std::vector<IntRectangle> halls;

		std::shared_ptr<Leaf> leftChild;
		std::shared_ptr<Leaf> rightChild;

	private:
		void createHall(std::shared_ptr<IntRectangle> left, std::shared_ptr<IntRectangle> right);
		std::shared_ptr<IntRectangle> getRoom();

		uint m_minHall;
		uint m_maxHall;
		std::shared_ptr<Random::Generator<> > generator;
		uint m_minSize;
	};
}
