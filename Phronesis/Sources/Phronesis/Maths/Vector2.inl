#pragma once

#include "Vector2.hpp"

namespace Phronesis
{
	template<typename T>
	Vector2T<T>::Vector2T() : glm::tvec2<T>(0, 0) {}

	template<typename T>
	Vector2T<T>::Vector2T(const T& val) : glm::tvec2<T>(val, val) {}

	template<typename T>
	Vector2T<T>::Vector2T(const T& x_val, const T& y_val) : glm::tvec2<T>(x_val, y_val) {}

	template<typename T>
	template<typename K>
	Vector2T<T>::Vector2T(const Vector2T<K>& source) : glm::tvec2<T>(static_cast<T>(source.x), static_cast<T>(source.y)) {}

	template<typename T>
	template<typename K>
	bool Vector2T<T>::operator==(const Vector2T<K> &other) const
	{
		//return detail::compute_equal<T, std::numeric_limits<T>::is_iec559>::call(this->x, other.x) &&
		//	   detail::compute_equal<T, std::numeric_limits<T>::is_iec559>::call(this->y, other.y);
		return this->x == other.x && this->y == other.y;
	}

	template<typename T>
	template<typename K>
	bool Vector2T<T>::operator!=(const Vector2T<K> &other) const
	{
		return !(*this == other);
	}
}
