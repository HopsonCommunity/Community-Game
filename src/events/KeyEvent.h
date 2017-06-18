#pragma once

#include "Event.h"

namespace Events
{
	enum class KeyModifier
	{
		SHIFT = BIT(0),
		CONTROL = BIT(1),
		ALT = BIT(2)
	};

	class KeyEvent : public Event
	{
	public:
		KeyEvent(int32 keyCode, Event::Type type);

		int32 getKeyCode() const { return m_keyCode; }

		static int32 getStaticType() { return (int32)Event::Type::KEY_PRESSED | (int32)Event::Type::KEY_RELEASED; }

	protected:
		int32 m_keyCode;
		int32 m_count;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int32 button, int32 repeat, int32 modifiers);

		int32 getRepeat() const { return m_repeat; }
		int32 getModifiers() const { return m_modifiers; }
		bool isModifier(int32 modifier) const { return (bool)(m_modifiers & modifier); }

		static Type getStaticType() { return Event::Type::KEY_PRESSED; }

	private:
		int32 m_repeat;
		int32 m_modifiers;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int32 button);

		static Type getStaticType() { return Event::Type::KEY_RELEASED; }
	};
}