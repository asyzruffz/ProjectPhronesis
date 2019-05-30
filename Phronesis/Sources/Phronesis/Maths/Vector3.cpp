
#include "StdAfx.hpp"
#include "Vector3.hpp"

using namespace Phronesis;

template<> const Vector3f Vector3f::zero = Vector3f(0.0f, 0.0f, 0.0f);
template<> const Vector3f Vector3f::one = Vector3f(1.0f, 1.0f, 1.0f);
template<> const Vector3f Vector3f::left = Vector3f(-1.0f, 0.0f, 0.0f);
template<> const Vector3f Vector3f::right = Vector3f(1.0f, 0.0f, 0.0f);
template<> const Vector3f Vector3f::up = Vector3f(0.0f, 1.0f, 0.0f);
template<> const Vector3f Vector3f::down = Vector3f(0.0f, -1.0f, 0.0f);
template<> const Vector3f Vector3f::forward = Vector3f(0.0f, 0.0f, 1.0f);
template<> const Vector3f Vector3f::back = Vector3f(0.0f, 0.0f, -1.0f);

template<> const Vector3d Vector3d::zero = Vector3d(0.0, 0.0, 0.0);
template<> const Vector3d Vector3d::one = Vector3d(1.0, 1.0, 1.0);
template<> const Vector3d Vector3d::left = Vector3d(-1.0, 0.0, 0.0);
template<> const Vector3d Vector3d::right = Vector3d(1.0, 0.0, 0.0);
template<> const Vector3d Vector3d::up = Vector3d(0.0, 1.0, 0.0);
template<> const Vector3d Vector3d::down = Vector3d(0.0, -1.0, 0.0);
template<> const Vector3d Vector3d::forward = Vector3d(0.0, 0.0, 1.0);
template<> const Vector3d Vector3d::back = Vector3d(0.0, 0.0, -1.0);

template<> const Vector3i Vector3i::zero = Vector3i(0, 0, 0);
template<> const Vector3i Vector3i::one = Vector3i(1, 1, 1);
template<> const Vector3i Vector3i::left = Vector3i(-1, 0, 0);
template<> const Vector3i Vector3i::right = Vector3i(1, 0, 0);
template<> const Vector3i Vector3i::up = Vector3i(0, 1, 0);
template<> const Vector3i Vector3i::down = Vector3i(0, -1, 0);
template<> const Vector3i Vector3i::forward = Vector3i(0, 0, 1);
template<> const Vector3i Vector3i::back = Vector3i(0, 0, -1);

template<> const Vector3ui Vector3ui::zero = Vector3ui(0, 0, 0);
template<> const Vector3ui Vector3ui::one = Vector3ui(1, 1, 1);
