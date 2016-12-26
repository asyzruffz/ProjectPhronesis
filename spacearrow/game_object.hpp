/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "entity.hpp"

class GameObject : public Entity
{
public:

	GameObject(string name = "GameObject");
	
	virtual void start();
	virtual void update(float dt);
	virtual void fixedUpdate(float dt);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif // GAME_OBJECT_HPP