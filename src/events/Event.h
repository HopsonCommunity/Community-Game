#pragma once

#include "../Common.h"

#undef MOUSE_MOVED

namespace Events
{
	class Event
	{
	private:
		friend class EventDispatcher;

	public:
		enum class Type
		{
			KEY_PRESSED = BIT(0),
			KEY_RELEASED = BIT(1),

			MOUSE_PRESSED = BIT(2),
			MOUSE_RELEASED = BIT(3),
			MOUSE_MOVED = BIT(4),

			WINDOW_RESIZE = BIT(5),
		};

	protected:
		bool m_handled;
		Type m_type;

	protected:
		Event(Type type);

	public:
		Type getType() const { return m_type; }
		bool isHandled() const { return m_handled; }

		static std::string typeToString(Type type);
	};
}