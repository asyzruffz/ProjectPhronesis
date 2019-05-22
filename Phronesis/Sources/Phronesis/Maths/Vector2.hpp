#pragma once

namespace Phronesis
{
	template<typename T>
	class Vector2T
	{
	public:
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

		T x, y;
	};

	using Vector2f = Vector2T<float>;
	using Vector2d = Vector2T<double>;
	using Vector2i = Vector2T<int32_t>;
	using Vector2ui = Vector2T<uint32_t>;
	using Vector2 = Vector2f;
}

#include "Vector2.inl"
