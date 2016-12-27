/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#ifndef COMPONENT_EXT_HPP
#define COMPONENT_EXT_HPP

#include "entity.hpp"
#include "component.hpp"

template <typename T>
bool Component::hasComponent() const
{
	assert(mp_owner != nullptr);
	return mp_owner->hasComponent<T>();
}

template <typename T>
T& Component::getComponent()
{
	assert(mp_owner != nullptr);
	return mp_owner->getComponent<T>();
}

#endif // COMPONENT_EXT_HPP
