#pragma once

#include "Event.h"
#include "../maths/Vec2.h"

namespace Events
{
	class MouseButtonEvent : public Event
	{
	protected:
		MouseButtonEvent(int32 button, float x, float y, Event::Type type);

	public:
		const int32 getButton() const { return m_button; }
		const float getX() const { return m_position.x; }
		const float getY() const { return m_position.y; }
		const Vec2& getPosition() const { return m_position; }

		static int32 getStaticType() { return (int32)Event::Type::MOUSE_PRESSED | (int32)Event::Type::MOUSE_RELEASED; }

	protected:
		int32 m_button;
		Vec2 m_position;
	};

	class MousePressedEvent : public MouseButtonEvent
	{
	public:
		MousePressedEvent(int32 button, float x, float y);

		static Type getStaticType() { return Event::Type::MOUSE_PRESSED; }
	};

	class MouseReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseReleasedEvent(int32 button, float x, float y);

		static Type GetStaticType() { return Event::Type::MOUSE_RELEASED; }
	};

	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y, bool dragged);

		const float getX() const { return m_position.x; }
		const float getY() const { return m_position.y; }
		const Vec2& getPosition() const { return m_position; }
		const bool isDragged() const { return m_dragged; }

		static Type getStaticType() { return Event::Type::MOUSE_MOVED; }

	private:
		Vec2 m_position;
		bool m_dragged;
	};
}