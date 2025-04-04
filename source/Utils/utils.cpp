#include "utils.h"

namespace utls
{
	float randFloat(float begin, float end)
	{
		return ((end - begin) * ((float)rand() / RAND_MAX)) + begin;
	}

	Timer::Timer(float waitTime, float* dt)
	{
		if (waitTime <= 0)
		{
			throw("Wait time has to be more then 0");
		}
		m_waitTime = waitTime;
		m_dt_ptr = dt;
	}

	bool Timer::isEnded()
	{
		if (m_isActive)
		{
			if (check())
				m_isActive = false;
		}
		else
		{
			activate();
			return true;
		}

		return false;
	}

	void Timer::activate()
	{
		m_isActive = true;
	}

	void Timer::stop()
	{
		m_currentTime = 0;
		m_isActive = false;
	}

	bool Timer::check()
	{
		m_currentTime += *m_dt_ptr;
		if (m_currentTime >= m_waitTime)
		{
			m_currentTime = 0;
			return true;
		}

		return false;
	}
}