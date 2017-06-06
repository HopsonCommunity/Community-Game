#pragma once

#include "../Common.h"

#include "../graphics/gui/Window.h"

namespace Debug
{
	class Console : public GUI::Window
	{
	public:
		Console();
		~Console();

	private:
		GUI::Panel* m_panel;
	};
}