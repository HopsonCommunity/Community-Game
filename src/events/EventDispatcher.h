#pragma once

#include "Event.h"

namespace Events
{
	class EventDispatcher
	{
	private:
		Event& m_event;
	public:
		EventDispatcher(Event& event)
			: m_event(event) {}

		template<typename T>
		void dispatch(std::function<bool(T&)> func)
		{
			if ((int32)m_event.getType() & (int32)T::getStaticType())
				m_event.m_handled = func(*(T*)&m_event);
		}
	};
}