#pragma once

#include "Vector3.hpp"

namespace Phronesis
{
	template<typename T>
	Vector3T<T>::Vector3T() : glm::tvec3<T>(0, 0) {}

	template<typename T>
	Vector3T<T>::Vector3T(const T& val) : glm::tvec3<T>(val, val, val) {}

	template<typename T>
	Vector3T<T>::Vector3T(const T& x_val, const T& y_val, const T& z_val) : glm::tvec3<T>(x_val, y_val, z_val) {}

	template<typename T>
	template<typename K>
	Vector3T<T>::Vector3T(const Vector3T<K>& source) : glm::tvec3<T>(static_cast<T>(source.x), static_cast<T>(source.y), static_cast<T>(source.z)) {}

	template<typename T>
	template<typename K>
	bool Vector3T<T>::operator==(const Vector3T<K> &other) const
	{
		return 
			detail::compute_equal<T, std::numeric_limits<T>::is_iec559>::call(x, other.x) &&
			detail::compute_equal<T, std::numeric_limits<T>::is_iec559>::call(y, other.y) &&
			detail::compute_equal<T, std::numeric_limits<T>::is_iec559>::call(z, other.z);
		//return x == other.x && y == other.y && z == other.z;
	}

	template<typename T>
	template<typename K>
	bool Vector3T<T>::operator!=(const Vector3T<K> &other) const
	{
		return !(*this == other);
	}
}
