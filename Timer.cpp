#include "Timer.h"

Timer::Timer()
	: m_timeElasped(0),
	m_expirationTime(0),
	m_isActive(false),
	m_isFinished(false)
{
}

void Timer::activate()
{
	if (isActive())
	{
		return;
	}

	m_isActive = true;
	m_isFinished = false;
}

void Timer::update(const float deltaTime)
{
	if (m_isActive)
	{
		m_timeElasped += deltaTime;

		if (isExpired())
		{
			deactivate();
		}
	}
}

void Timer::deactivate()
{
	m_isActive = false;
	m_isFinished = true;
	m_timeElasped = 0;
}