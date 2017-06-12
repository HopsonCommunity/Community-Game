#include "DebugConsole.h"

namespace Debug
{
	using namespace GUI;

	Console::Console()
		: Window("Console", FloatRectangle(600.f, 300.f, 200.f, 150.f), { 65.f, 40.f })
		, m_panel(new Panel())
	{
		m_panel->add(this);
	}

	Console::~Console()
	{
		delete m_panel;
	}
}
