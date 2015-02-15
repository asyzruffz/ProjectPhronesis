/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#include "phro_sprite_node.hpp"

SpriteNode::SpriteNode(const sf::Texture& texture)
{
	sSprite.setTexture(texture);
}

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& rect)
{
	sSprite.setTexture(texture);
	sSprite.setTextureRect(rect);
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sSprite, states);
}
