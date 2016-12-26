/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include <cassert>
#include <memory>
using namespace std;

class Entity;	// Forward declaration to avoid cyclic dependency

class Component
{
public:

	Component();

	typedef unique_ptr<Component> Ptr;

	virtual void awake() {}
	virtual void start() {}
	virtual void update(float dt) {}
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {}

	void setOwner(Entity* owner);

	template <typename T>
	bool hasComponent();
	template <typename T>
	T& getComponent();



protected: 
	
	Entity* m_owner;

};

#endif // COMPONENT_HPP