/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#include "phro_entity.hpp"

void Entity::setVelocity(sf::Vector2f velocity)
{
	vel = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
	vel.x = vx;
	vel.y = vy;
}

sf::Vector2f Entity::getVelocity() const
{
	return vel;
}

void Entity::updateCurrent(float dt)
{
	move(vel * dt);
}
