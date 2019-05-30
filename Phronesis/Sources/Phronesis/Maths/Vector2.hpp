#pragma once

#include <glm/glm.hpp>

namespace Phronesis
{
	template<typename T>
	struct Vector2T : public glm::tvec2<T>
	{
		Vector2T();

		explicit Vector2T(const T& val);

		Vector2T(const T& x_val, const T& y_val);

		template<typename K>
		Vector2T(const Vector2T<K>& source);

		template<typename K>
		bool operator==(const Vector2T<K> &other) const;

		template<typename K>
		bool operator!=(const Vector2T<K> &other) const;

		static const Vector2T zero;
		static const Vector2T one;
		static const Vector2T left;
		static const Vector2T right;
		static const Vector2T up;
		static const Vector2T down;
	};

	using Vector2f = Vector2T<float>;
	using Vector2d = Vector2T<double>;
	using Vector2i = Vector2T<int>;
	using Vector2ui = Vector2T<unsigned int>;
	using Vector2 = Vector2f;
}

#include "Vector2.inl"
