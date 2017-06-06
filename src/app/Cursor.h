#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#ifdef SFML_SYSTEM_WINDOWS
	#include <windows.h>
#elif defined(SFML_SYSTEM_LINUX)
	#include <X11/cursorfont.h>
	#include <X11/Xlib.h>
#else
	#error This OS is not yet supported by the cursor library.
#endif

class StandardCursor
{
private:
#ifdef SFML_SYSTEM_WINDOWS
	HCURSOR Cursor;
#else
	XID Cursor;
	Display* display;
#endif
public:
	enum TYPE 
	{ 
		WAIT, TEXT, NORMAL, HAND, SIZENWSE
	};

	StandardCursor(const TYPE t);
	~StandardCursor();

	void set(const sf::WindowHandle& aWindowHandle) const;
};
