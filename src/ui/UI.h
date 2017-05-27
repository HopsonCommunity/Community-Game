#pragma once

#include "UIComponentBase.h"

#include "../app/input/Input.h"
#include "../maths/Maths.h"

#include <vector>
#include <memory>

namespace UI
{
	class UI
	{
	public:
		explicit UI(sf::RenderWindow* owningWindow);
		~UI();

		void addComponent(UIComponent& component);

		void update(Input::Input& input);
		void render();
	private:
		std::vector<UIComponent*> m_components;
		sf::RenderWindow* m_owningWindow;
		sf::View m_uiView;

		bool m_mousePressed;
	};
}
