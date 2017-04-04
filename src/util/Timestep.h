#pragma once

struct Timestep
{
private:
	float m_timestep;
	float m_lastTime;
public:
	inline Timestep(float initialTime)
		: m_timestep(0.0f), m_lastTime(initialTime)
	{
	}

	inline void update(float currentTime)
	{
		m_timestep = currentTime - m_lastTime;
		m_lastTime = currentTime;
	}

	inline float asSeconds() const { return asMillis() * 0.001f; }
	inline float asMillis() const { return m_timestep; }
};