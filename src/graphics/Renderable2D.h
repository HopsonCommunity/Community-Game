#pragma once

#include "../Common.h"

#include "../maths/maths.h"
#include "../maths/Color.h"

#include <SFML/Graphics/Texture.hpp>

namespace Graphics
{
	class Renderable2D
	{
	public:
		Renderable2D(const Vec2& position, const Vec2& size, const Color& color)
			: m_position(position)
			, m_size(size)
			, m_color(color)
		{
			m_UVs.push_back(Vec2());
			m_UVs.push_back(Vec2());
			m_UVs.push_back(Vec2());
			m_UVs.push_back(Vec2());
		}

		const Vec2& getPosition() const { return m_position; }
		const Vec2& getSize() const { return m_size; }
		const Color& getColor() const { return m_color; }
		const std::vector<Vec2>& getUVs() const { return m_UVs; }

	public:
		Vec2 m_position;
		Vec2 m_size;
		Color m_color;
		std::vector<Vec2> m_UVs;
	};
}