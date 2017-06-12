#pragma once

#include "../Common.h"

#include "Renderable2D.h"

#include <SFML/Graphics.hpp>

namespace Graphics
{
#define MAX_SUBMITS   50000
#define MAX_VERTICES  MAX_SUBMITS * 4

	class Renderer2D
	{
	public:
		// This class has support for two seperate draw calls
		// In level BEFORE and AFTER is used to render stuff
		// behind or infront of entities.
		enum class RenderOrder
		{
			BEFORE, AFTER
		};

		struct Render
		{
			sf::Vertex* buffer;
			sf::Vertex* bufferPtr;
			uint vertexCount;
		};
	public:
		Renderer2D();
		~Renderer2D();

		void begin();
		void submit(const Renderable2D* renderable, const RenderOrder& renderOrder = RenderOrder::BEFORE);
		void present(sf::RenderWindow& window, const RenderOrder& renderOrder = RenderOrder::BEFORE);

		sf::RenderStates m_states;

	private:
		Render m_before, m_after;

		void submit(const Renderable2D* renderable, Render& render);
	};
}