#include "MouseEvent.h"

namespace Events
{
	MouseButtonEvent::MouseButtonEvent(int32 button, float x, float y, Type type)
		: Event(type), m_button(button), m_position({ x, y })
	{
	}

	MousePressedEvent::MousePressedEvent(int32 button, float x, float y)
		: MouseButtonEvent(button, x, y, MousePressedEvent::getStaticType())
	{
	}

	MouseReleasedEvent::MouseReleasedEvent(int32 button, float x, float y)
		: MouseButtonEvent(button, x, y, MouseReleasedEvent::GetStaticType())
	{
	}

	MouseMovedEvent::MouseMovedEvent(float x, float y, bool dragged)
		: Event(MouseMovedEvent::getStaticType()), m_position({ x, y }), m_dragged(dragged)
	{
	}
}
