#pragma once
#include <vector>
#include <map>
#include "SFML/Graphics.hpp"
#include <math.h>
#include <functional>

namespace utls
{
	/*
		Functions
	*/

	float randFloat(float begin, float end);

	// Vectors
	template <class T>
	float getMagnitude(const T& vector)
	{
		return sqrt(vector.x * vector.x + vector.y * vector.y);
	}

	template <class T>
	sf::Vector2f getNormal(const T& vector) {
		float length = sqrt(vector.x * vector.x + vector.y * vector.y);
		if (length != 0)
			return sf::Vector2f(vector.x / length, vector.y / length);
		else
			return sf::Vector2f(0, 0); // Avoid division by zero
	}


	/*
		Classes
	*/

	class Timer
	{
	public:
		Timer(float waitTime, float* dt);

		bool isEnded();
		void activate();
		void stop();

	private:
		float* m_dt_ptr;
		float m_waitTime;
		float m_currentTime = 0;
		bool m_isActive = false;

		bool check();
	};

	// Binds at function, when value is changed by '=' it will run a function
	template <class T>
	struct EventVar
	{
		T value;
		std::function<void()> onValueChanged = nullptr;

		EventVar(T value): value(value), onValueChanged(nullptr) {}
		EventVar(){}
		~EventVar() {}
		EventVar& operator= (const T& newVal)
		{
			if (value != newVal)
			{
				value = newVal;
				if (onValueChanged)
				{
					onValueChanged();
				}
			}
			return *this;
		}

		void bind(std::function<void()> callback)
		{
			onValueChanged = callback;
		}

		operator T() const
		{
			return value;
		}

		T& get()
		{
			return value;
		}

		T* operator->() {
			return &value;
		}

		const T* operator->() const {
			return &value;
		}

		EventVar& operator+= (const T& other)
		{
			value += other;
			if (onValueChanged)
			{
				onValueChanged();
			}

			return *this;
		}
	};
}