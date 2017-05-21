#pragma once

#include "../app/input/Input.h"
#include "../maths/Maths.h"

#include <SFML/Graphics.hpp>

#include <memory>

namespace UI
{
	class UIComponent
	{
	public:
		virtual ~UIComponent() = default;
		explicit UIComponent(sf::Rect<int> transform) : m_transform(transform) { }

		virtual void hover(int x, int y) = 0;
		virtual void click(int x, int y) = 0;
		virtual void clickAndHold(int x, int y) = 0;
		virtual void none() = 0;

		virtual void render(sf::RenderWindow& window) = 0;

		const sf::Rect<int>& getTransform() const { return m_transform; }
	protected:
		sf::Rect<int> m_transform;
	};
}
