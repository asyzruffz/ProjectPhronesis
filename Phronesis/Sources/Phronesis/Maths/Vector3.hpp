#pragma once

#include <glm/glm.hpp>

namespace Phronesis
{
	template<typename T>
	struct Vector3T : public glm::tvec3<T>
	{
		Vector3T();

		explicit Vector3T(const T& val);

		Vector3T(const T& x_val, const T& y_val, const T& z_val);

		template<typename K>
		Vector3T(const Vector3T<K>& source);

		template<typename K>
		bool operator==(const Vector3T<K> &other) const;

		template<typename K>
		bool operator!=(const Vector3T<K> &other) const;

		static const Vector3T zero;
		static const Vector3T one;
		static const Vector3T left;
		static const Vector3T right;
		static const Vector3T up;
		static const Vector3T down;
		static const Vector3T forward;
		static const Vector3T back;
	};

	using Vector3f = Vector3T<float>;
	using Vector3d = Vector3T<double>;
	using Vector3i = Vector3T<int>;
	using Vector3ui = Vector3T<unsigned int>;
	using Vector3 = Vector3f;
}

#include "Vector3.inl"
