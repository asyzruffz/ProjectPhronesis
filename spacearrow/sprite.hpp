/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SFML/Graphics.hpp>

#include <string>
using namespace std;

#include "component.hpp"

class Sprite : public Component
{
public:
	
	Sprite(string spriteName) : m_spriteName(spriteName) {}

	virtual void awake();
	virtual void update(float dt);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setSpriteAnchor(const sf::Vector2f& origin);
	sf::Vector2f getSpriteSize();
	static float PIXEL_PER_METER;

private:

	string m_spriteName;
	sf::Sprite m_sprite;
	sf::Transform m_transform;

};

#endif // SPRITE_HPP
