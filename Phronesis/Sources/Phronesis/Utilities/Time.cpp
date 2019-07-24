
#include "StdAfx.hpp"
#include "Time.hpp"

using namespace Phronesis;

const std::chrono::time_point<std::chrono::high_resolution_clock> Time::start = std::chrono::high_resolution_clock::now();

Time Time::Seconds(const float& seconds)
{
	return Time(std::chrono::duration<float>(seconds));
}

Time Time::Milliseconds(const int& milliseconds)
{
	return Time(std::chrono::duration<int, std::micro>(milliseconds));
}

Time Time::Microseconds(const long long& microseconds)
{
	return Time(std::chrono::duration<long long, std::micro>(microseconds));
}

Time Time::now()
{
	return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);
}

std::string Time::dateTime(const std::string& format)
{
	auto timeT = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	std::stringstream ss;
	ss << std::put_time(std::localtime(&timeT), format.c_str());
	return ss.str();
}

float Time::asSeconds() const
{
	return static_cast<float>(microseconds.count()) / static_cast<float>(1000000);
}

int Time::asMilliseconds() const
{
	return static_cast<int>(microseconds.count()) / static_cast<int>(1000);
}

long long Time::asMicroseconds() const
{
	return static_cast<long long>(microseconds.count());
}

bool Time::operator==(const Time& other) const
{
	return microseconds == other.microseconds;
}

bool Time::operator!=(const Time& other) const
{
	return microseconds != other.microseconds;
}

bool Time::operator<(const Time& other) const
{
	return microseconds < other.microseconds;
}

bool Time::operator<=(const Time& other) const
{
	return microseconds <= other.microseconds;
}

bool Time::operator>(const Time& other) const
{
	return microseconds > other.microseconds;
}

bool Time::operator>=(const Time& other) const
{
	return microseconds >= other.microseconds;
}

Time Time::operator-() const
{
	return Time(-microseconds);
}

Time Phronesis::operator+(const Time& left, const Time& right)
{
	return left.microseconds + right.microseconds;
}

Time Phronesis::operator-(const Time& left, const Time& right)
{
	return left.microseconds - right.microseconds;
}

Time Phronesis::operator*(const Time& left, const float& right)
{
	return left.microseconds * right;
}

Time Phronesis::operator*(const float& left, const Time& right)
{
	return right * left;
}

Time Phronesis::operator/(const Time& left, const float& right)
{
	return left.microseconds / right;
}

double Phronesis::operator/(const Time& left, const Time& right)
{
	return static_cast<double>(left.microseconds.count()) / static_cast<double>(right.microseconds.count());
}

Time& Time::operator+=(const Time& other)
{
	return *this = *this + other;
}

Time& Time::operator-=(const Time& other)
{
	return *this = *this - other;
}

Time& Time::operator*=(const float& other)
{
	return *this = *this * other;
}

Time& Time::operator/=(const float& other)
{
	return *this = *this / other;
}
