#include "Cursor.h"

#ifdef SFML_SYSTEM_WINDOWS

StandardCursor::StandardCursor(const TYPE t)
{
	switch (t)
	{
	case StandardCursor::WAIT:
		Cursor = LoadCursor(NULL, IDC_WAIT);
		break;
	case StandardCursor::HAND:
		Cursor = LoadCursor(NULL, IDC_HAND);
		break;
	case StandardCursor::NORMAL:
		Cursor = LoadCursor(NULL, IDC_ARROW);
		break;
	case StandardCursor::TEXT:
		Cursor = LoadCursor(NULL, IDC_IBEAM);
		break;
	case StandardCursor::SIZENWSE:
		Cursor = LoadCursor(NULL, IDC_SIZENWSE);
		break;
	}
}

void StandardCursor::set(const sf::WindowHandle& aWindowHandle) const
{
	SetClassLongPtr(aWindowHandle, GCLP_HCURSOR, reinterpret_cast<LONG_PTR>(Cursor));
}

StandardCursor::~StandardCursor()
{
}

#elif defined(SFML_SYSTEM_LINUX)

StandardCursor::StandardCursor(const TYPE t)
{
	display = XOpenDisplay(NULL);

	switch (t)
	{
	case StandardCursor::WAIT:
		Cursor = XCreateFontCursor(display, XC_watch);
		break;
	case StandardCursor::HAND:
		Cursor = XCreateFontCursor(display, XC_hand1);
		break;
	case StandardCursor::NORMAL:
		Cursor = XCreateFontCursor(display, XC_left_ptr);
		break;
	case StandardCursor::TEXT:
		Cursor = XCreateFontCursor(display, XC_xterm);
		break;
	case StandardCursor::SIZENWSE:
		Cursor = XCreateFontCursor(display, XC_bottom_right_corner);
		break;
		// For more cursor options on Linux go here:
		// http://www.tronche.com/gui/x/xlib/appendix/b/
	}
}

void StandardCursor::set(const sf::WindowHandle& aWindowHandle) const
{
	XDefineCursor(display, aWindowHandle, Cursor);
	XFlush(display);
}

StandardCursor::~StandardCursor()
{
	XFreeCursor(display, Cursor);
	delete display;
	display = NULL;
}

#else
#error This OS is not yet supported by the cursor library.
#endif