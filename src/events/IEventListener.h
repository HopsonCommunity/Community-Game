#pragma once

#include "Event.h"

namespace Events 
{
	class IEventListener
	{
	public:
		virtual void onEvent(Event& event) = 0;
	};
}