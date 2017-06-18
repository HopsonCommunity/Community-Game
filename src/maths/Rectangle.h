#pragma once

#include "Vec2.h"

#include "../Types.h"

struct FloatRectangle
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

	FloatRectangle();
	FloatRectangle(const Vec2& position, const Vec2& size);
	FloatRectangle(float x, float y, float width, float height);

	bool intersects(const FloatRectangle& other) const;
	bool contains(const Vec2& point) const;

	Vec2 getMinimumBound() const { return position; }
	Vec2 getMaximumBound() const { return position + size; }
};

struct IntRectangle
{
	union
	{
		Vec2i position;
		struct
		{
			int32 x;
			int32 y;
		};
	};
	union
	{
		Vec2i size;
		struct
		{
			int32 width;
			int32 height;
		};
	};

	IntRectangle();
	IntRectangle(const Vec2i& min, const Vec2i& max);
	IntRectangle(int32 x, int32 y, int32 width, int32 height);

	bool intersects(const IntRectangle& other) const;
	bool contains(const Vec2i& point);

	Vec2i getMinimumBound() const { return position; }
	Vec2i getMaximumBound() const { return position + size; }
};
