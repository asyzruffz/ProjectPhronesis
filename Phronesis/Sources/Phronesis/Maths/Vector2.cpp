
#include "StdAfx.hpp"
#include "Vector2.hpp"

using namespace Phronesis;

template<> const Vector2f Vector2f::zero = Vector2f(0.0f, 0.0f);
template<> const Vector2f Vector2f::one = Vector2f(1.0f, 1.0f);
template<> const Vector2f Vector2f::left = Vector2f(-1.0f, 0.0f);
template<> const Vector2f Vector2f::right = Vector2f(1.0f, 0.0f);
template<> const Vector2f Vector2f::up = Vector2f(0.0f, 1.0f);
template<> const Vector2f Vector2f::down = Vector2f(0.0f, -1.0f);

template<> const Vector2d Vector2d::zero = Vector2d(0.0, 0.0);
template<> const Vector2d Vector2d::one = Vector2d(1.0, 1.0);
template<> const Vector2d Vector2d::left = Vector2d(-1.0, 0.0);
template<> const Vector2d Vector2d::right = Vector2d(1.0, 0.0);
template<> const Vector2d Vector2d::up = Vector2d(0.0, 1.0);
template<> const Vector2d Vector2d::down = Vector2d(0.0, -1.0);

template<> const Vector2i Vector2i::zero = Vector2i(0, 0);
template<> const Vector2i Vector2i::one = Vector2i(1, 1);
template<> const Vector2i Vector2i::left = Vector2i(-1, 0);
template<> const Vector2i Vector2i::right = Vector2i(1, 0);
template<> const Vector2i Vector2i::up = Vector2i(0, 1);
template<> const Vector2i Vector2i::down = Vector2i(0, -1);

template<> const Vector2ui Vector2ui::zero = Vector2ui(0, 0);
template<> const Vector2ui Vector2ui::one = Vector2ui(1, 1);
