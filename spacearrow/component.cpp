/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#include "entity.hpp"
#include "component.hpp"

Component::Component()
{
	mp_owner = nullptr;
}

void Component::setOwner(Entity* owner)
{
	mp_owner = owner;
}
