#pragma once

struct Timestep
{
private:
	float m_timestep;
	float m_lastTime;
public:
	explicit Timestep(float initialTime)
		: m_timestep(0.0f), m_lastTime(initialTime)
	{
	}

	void update(float currentTime)
	{
		m_timestep = currentTime - m_lastTime;
		m_lastTime = currentTime;
	}

	float asSeconds() const { return asMillis() * 0.001f; }
	float asMillis() const { return m_timestep; }
};