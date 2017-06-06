#include "Event.h"

namespace Events
{
	Event::Event(Type type)
		: m_type(type), m_handled(false)
	{
	}

	std::string Event::typeToString(Type type)
	{
		switch (type)
		{
		case Type::KEY_PRESSED:
			return "KEY_PRESSED";
		case Type::KEY_RELEASED:
			return "KEY_RELEASED";
		case Type::MOUSE_PRESSED:
			return "MOUSE_PRESSED";
		case Type::MOUSE_RELEASED:
			return "MOUSE_RELEASED";
		case Type::MOUSE_MOVED:
			return "MOUSE_MOVED";
		}
		return "INVALID";
	}
}