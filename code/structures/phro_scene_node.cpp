/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#include "phro_scene_node.hpp"

void SceneNode::attachChild(Ptr child)
{
	child->parent = this;
	children.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
	vector<Ptr>::iterator found;
	found = find_if(children.begin(), children.end(), [&] (Ptr& p) -> bool { return p.get() == &node; } );
	
	assert(found != children.end()); // debug
	
	Ptr result = std::move(*found);
	result->parent = nullptr;
	children.erase(found);
	return result;
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	drawCurrent(target, states);
	for(auto it = children.begin(); it != children.end(); it++)
		(*it)->draw(target, states);
}

void SceneNode::update(float dt)
{
	updateCurrent(dt);
	updateChildren(dt);
}

void SceneNode::updateChildren(float dt)
{
	for(auto it = children.begin(); it != children.end(); it++)
		(*it)->update(dt);
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;
	for(const SceneNode* node = this; node != nullptr; node = node->parent)
		transform = transform * node->getTransform();
	return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}
