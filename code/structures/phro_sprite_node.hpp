/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#ifndef PHRO_SPRITE_NODE_HPP
#define PHRO_SPRITE_NODE_HPP

#include <SFML/Graphics.hpp>

#include "phro_scene_node.hpp"

class SpriteNode : public SceneNode
{
public:
	
	explicit SpriteNode(const sf::Texture& texture);
	SpriteNode(const sf::Texture& texture, const sf::IntRect& rect);
	
private:
	
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	
	sf::Sprite sSprite;
};

#endif // PHRO_SPRITE_NODE_HPP
