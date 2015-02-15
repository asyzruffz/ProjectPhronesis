/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#ifndef PHRO_ENTITY_HPP
#define PHRO_ENTITY_HPP

#include <SFML/Graphics.hpp>

#include "phro_scene_node.hpp"

class Entity : public SceneNode
{
public:
	
	void setVelocity(sf::Vector2f velocity);
	void setVelocity(float vx, float vy);
	sf::Vector2f getVelocity() const;
	
private:
	
	virtual void updateCurrent(float dt);
	
	sf::Vector2f vel;
};

#endif // PHRO_ENTITY_HPP
