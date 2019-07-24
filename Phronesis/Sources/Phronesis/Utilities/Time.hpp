#pragma once

#include <string>
#include <chrono>

namespace Phronesis
{
	class Time
	{
	public:
		Time() = default;

		static Time Seconds(const float& seconds);
		static Time Milliseconds(const int& milliseconds);
		static Time Microseconds(const long long& microseconds);

		static Time now();
		static std::string dateTime(const std::string& format = "%Y-%m-%d %H:%M:%S");

		float asSeconds() const;
		int asMilliseconds() const;
		long long asMicroseconds() const;

		bool operator==(const Time& other) const;
		bool operator!=(const Time& other) const;
		bool operator<(const Time& other) const;
		bool operator<=(const Time& other) const;
		bool operator>(const Time& other) const;
		bool operator>=(const Time& other) const;
		Time operator-() const;
		friend Time operator+(const Time& left, const Time& right);
		friend Time operator-(const Time& left, const Time& right);
		friend Time operator*(const Time& left, const float& right);
		friend Time operator*(const float& left, const Time& right);
		friend Time operator/(const Time& left, const float& right);
		friend double operator/(const Time& left, const Time& right);
		Time& operator+=(const Time& other);
		Time& operator-=(const Time& other);
		Time& operator*=(const float& other);
		Time& operator/=(const float& other);

	private:
		template<typename Rep, typename Period>
		constexpr Time(const std::chrono::duration<Rep, Period> &duration) :
			microseconds{ std::chrono::duration_cast<std::chrono::microseconds>(duration).count() }
		{
		}

	private:
		static const std::chrono::time_point<std::chrono::high_resolution_clock> start;
		std::chrono::microseconds microseconds{};
	};
}
