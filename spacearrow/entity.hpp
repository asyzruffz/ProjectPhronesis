/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
#include <vector>
#include <typeindex>
#include <map>
#include <memory>
using namespace std;

#include "component.hpp"

class Entity
{
public:

	Entity();

	template <typename T>
	void addComponent();
	template <typename T>
	bool hasComponent();
	template <typename T>
	T& getComponent();

	typedef shared_ptr<Entity> Ptr;

	void setParent(Entity* parent);
	vector<Entity::Ptr>& getChildren();
	void setEnabled(bool isEnabled);
	bool isEnabled();

protected:

	map<type_index, Component::Ptr> m_components;
	Entity::Ptr mp_parent;

private:

	string m_name;
	vector<Entity::Ptr> m_children;
	bool m_enabled;

};

template <typename T>
void Entity::addComponent()
{
	T newComponent;
	newComponent.setOwner(this);
	newComponent.awake();
	m_components[typeid(T)] = Component::Ptr(&newComponent);
}

template <typename T>
bool Entity::hasComponent()
{
	return m_components.count(typeid(T)) > 0;
}

template <typename T>
T& Entity::getComponent()
{
	return (T)*m_components[typeid(T)];
}

#endif // ENTITY_HPP