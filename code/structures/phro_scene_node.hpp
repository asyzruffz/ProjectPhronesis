/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#ifndef PHRO_SCENE_NODE_HPP
#define PHRO_SCENE_NODE_HPP

#include <SFML/Graphics.hpp>

#include <memory>
#include <utility>     // move
#include <algorithm>   // find_if
#include <vector>
#include <cassert>
using namespace std;

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
	
	typedef unique_ptr<SceneNode> Ptr;
	
	SceneNode(): parent(nullptr) {}
	void attachChild(Ptr child);
	Ptr detachChild(const SceneNode& node);
	
	void update(float dt);
	sf::Transform getWorldTransform() const;
	sf::Vector2f getWorldPosition() const;
	
private:
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void updateCurrent(float dt) {}
	void updateChildren(float dt);
	
	// To be overridden by classes deriving from SceneNode
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	
	vector<Ptr> children;
	SceneNode* parent;
};

#endif // PHRO_SCENE_NODE_HPP
