#pragma once

#include "../../Common.h"

#include "../../maths/Maths.h"

#include <memory>

namespace WGenerator
{
	class Leaf
	{
	public:
		Leaf(maths::IntRectangle t_block, std::shared_ptr<Random::Generator<> > t_generator, uint t_minSize);

		bool split();
		void createRooms();

		std::shared_ptr<maths::IntRectangle> room;
		maths::IntRectangle block;

		std::vector<maths::IntRectangle> halls;

		std::shared_ptr<Leaf> leftChild;
		std::shared_ptr<Leaf> rightChild;

	private:
		void createHall(std::shared_ptr<maths::IntRectangle> left, std::shared_ptr<maths::IntRectangle> right);
		std::shared_ptr<maths::IntRectangle> getRoom();

		std::shared_ptr<Random::Generator<> > generator;
		uint m_minSize = 7;
	};
}
