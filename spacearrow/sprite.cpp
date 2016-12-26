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

float Sprite::PIXEL_PER_METER = 32.0f;

void Sprite::awake()
{
	m_sprite.setTexture(GameData::instance().rscStorage.getTextureRef(m_spriteName));
}

void Sprite::update(float dt)
{
	// Update the transform of the sprite from the Transform2D component
	Transform2D trans = getComponent<Transform2D>();
	m_transform = sf::Transform::Identity;
	m_transform.translate(trans.getGlobalPosition() * PIXEL_PER_METER);
	m_transform.rotate(trans.getGlobalRotation());
	m_transform.scale(trans.getGlobalScale());
}

void Sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= m_transform;
	target.draw(m_sprite, states);
}

// clamp function to set the value fixed within range
template<class T>
constexpr const T& clamp(const T& v, const T& lo, const T& hi)
{
	return (v < lo) ? lo : (hi < v) ? hi : v;
}

void Sprite::setSpriteAnchor(const sf::Vector2f& anchor)
{
	// Clamp the anchor to (0,1)
	sf::Vector2f origin = sf::Vector2f(clamp(anchor.x, 0.0f, 1.0f), clamp(anchor.y, 0.0f, 1.0f));

	// Set the anchor to the sprite
	sf::IntRect spriteSize = m_sprite.getTextureRect();
	m_sprite.setOrigin(origin.x * spriteSize.width, origin.y * spriteSize.height);
}
