/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#include "entity.hpp"

Entity::Entity()
{
	m_name = "Default Entity";
	m_enabled = true;
}

void Entity::setParent(Entity* parent)
{
	mp_parent = Entity::Ptr(parent);
	parent->getChildren().push_back(Entity::Ptr(this));
}

vector<Entity::Ptr>& Entity::getChildren()
{
	return m_children;
}

void Entity::setEnabled(bool isEnabled)
{
	m_enabled = isEnabled;
}

bool Entity::isEnabled()
{
	return m_enabled;
}