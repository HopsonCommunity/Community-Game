#include "Renderer2D.h"

#include "../maths/maths.h"
#include "../maths/Color.h"

namespace Graphics
{
	Renderer2D::Renderer2D()
	{
		m_before.buffer = new sf::Vertex[MAX_VERTICES];
		m_before.vertexCount = 0;

		m_after.buffer = new sf::Vertex[MAX_VERTICES];
		m_after.vertexCount = 0;
	}

	Renderer2D::~Renderer2D()
	{
		delete m_before.buffer;
		delete m_after.buffer;
	}

	void Renderer2D::begin()
	{
		m_before.bufferPtr = m_before.buffer;
		m_after.bufferPtr = m_after.buffer;
	}	

	void Renderer2D::submit(const Renderable2D* renderable, const RenderOrder& renderOrder)
	{
		if (renderOrder == RenderOrder::BEFORE)
			submit(renderable, m_before);
		if (renderOrder == RenderOrder::AFTER)
			submit(renderable, m_after);
	}
	
	void Renderer2D::present(sf::RenderWindow& window, const RenderOrder& renderOrder)
	{
		if (renderOrder == RenderOrder::BEFORE)
		{
			window.draw(m_before.buffer, m_before.vertexCount, sf::Quads, m_states);
			m_before.vertexCount = 0;
		}
		if (renderOrder == RenderOrder::AFTER)
		{
			window.draw(m_after.buffer, m_after.vertexCount, sf::Quads, m_states);
			m_after.vertexCount = 0;
		}
	}

	void Renderer2D::submit(const Renderable2D* renderable, Render& render)
	{
		const Vec2& position = renderable->getPosition();
		const Vec2& size = renderable->getSize();
		const Color& c = renderable->getColor();
		const std::vector<Vec2>& m_UVs = renderable->getUVs();

		Vec2* uvPtr = const_cast<Vec2*>(&m_UVs[0]);

		render.bufferPtr->position = position;
		render.bufferPtr->color = c;
		render.bufferPtr->texCoords = *uvPtr++;
		render.bufferPtr++;
		
		render.bufferPtr->position = Vec2(position.x, position.y + size.y);
		render.bufferPtr->color = c;
		render.bufferPtr->texCoords = *uvPtr++;
		render.bufferPtr++;
		
		render.bufferPtr->position = Vec2(position.x + size.x, position.y + size.y);
		render.bufferPtr->color = c;
		render.bufferPtr->texCoords = *uvPtr++;
		render.bufferPtr++;
		
		render.bufferPtr->position = Vec2(position.x + size.x, position.y);
		render.bufferPtr->color = c;
		render.bufferPtr->texCoords = *uvPtr++;
		render.bufferPtr++;

		render.vertexCount += 4;
	}
}
