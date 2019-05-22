#pragma once

#include "Vector2.hpp"

namespace Phronesis
{
	template<typename T>
	Vector2T<T>::Vector2T() : x(0), y(0) {}

	template<typename T>
	Vector2T<T>::Vector2T(const T& val) : x(val), y(val) {}

	template<typename T>
	Vector2T<T>::Vector2T(const T& x_val, const T& y_val) : x(x_val), y(y_val) {}

	template<typename T>
	template<typename K>
	Vector2T<T>::Vector2T(const Vector2T<K>& source) : x(static_cast<T>(source.x)), y(static_cast<T>(source.y)) {}

	template<typename T>
	template<typename K>
	bool Vector2T<T>::operator==(const Vector2T<K> &other) const
	{
		return x == other.x && y == other.y;
	}

	template<typename T>
	template<typename K>
	bool Vector2T<T>::operator!=(const Vector2T<K> &other) const
	{
		return !(*this == other);
	}
}
