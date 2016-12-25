/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#include "sprite.hpp"

#include "component.ext.hpp"
#include "game_data.hpp"
#include "transform_2d.hpp"

void Sprite::awake()
{
	m_sprite.setTexture(GameData::instance().rscStorage.getTextureRef(m_spriteName));
}

void Sprite::update(float dt)
{
	// Update the transform of the sprite from the Transform2D component
	Transform2D trans = getComponent<Transform2D>();
	m_transform = trans.getGlobalTransform();
}

void Sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= m_transform;
	target.draw(m_sprite, states);
}
