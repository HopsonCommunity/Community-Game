#pragma once

#include "Vec2.h"

#include "../Types.h"

namespace maths
{
	struct Rectangle
	{
		union
		{
			Vec2 position;
			struct
			{
				float x;
				float y;
			};
		};
		union
		{
			Vec2 size;
			struct
			{
				float width;
				float height;
			};
		};

		Rectangle();
		Rectangle(const Vec2& position, const Vec2& size);
		Rectangle(float x, float y, float width, float height);

		bool intersects(const Rectangle& other) const;
		bool contains(const Vec2& point) const;

		Vec2 getMinimumBound() const { return position; }
		Vec2 getMaximumBound() const { return position + size; }
	};

	struct IntRectangle
	{
		int32 x, y, width, height;

		IntRectangle();
		IntRectangle(int32 x, int32 y, int32 width, int32 height);
		IntRectangle(Vec2i min, Vec2i max);

		bool contains(Vec2i point);
	};
}