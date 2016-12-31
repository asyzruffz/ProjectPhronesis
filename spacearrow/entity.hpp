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

	Entity(string name = "Default Entity");
	virtual ~Entity() {}

	template <typename T, typename... Args>
	void addComponent(Args... args);
	template <typename T>
	bool hasComponent();
	template <typename T>
	T& getComponent();

	typedef shared_ptr<Entity> Ptr;

	Entity::Ptr setParent(Entity* parent);
	Entity::Ptr setParent(Entity::Ptr parent);
	Entity::Ptr getParent();
	vector<Entity::Ptr>& getChildren();
	void setEnabled(bool isEnabled);
	bool isEnabled() const;
	string getName() const;
	int getId() const;
	const vector<Entity::Ptr>& allChildren() const; // used to iterate without changing the value (e.g. for drawing)

protected:

	map<type_index, Component::Ptr> m_components;
	Entity::Ptr mp_parent;
	vector<Entity::Ptr> m_children;

private:

	static int s_entityCounter;
	int m_id;
	string m_name;
	bool m_enabled;

};

template <typename T, typename... Args>
void Entity::addComponent(Args... args)
{
	T* newComponent = new T(args...);
	m_components[typeid(T)] = Component::Ptr(newComponent);
	newComponent->setGameObject(this);
	newComponent->awake();
}

template <typename T>
bool Entity::hasComponent()
{
	return m_components.count(typeid(T)) > 0;
}

template <typename T>
T& Entity::getComponent()
{
	return *((T*)m_components[typeid(T)].get());
}

#endif // ENTITY_HPP