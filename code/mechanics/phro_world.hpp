/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#ifndef PHRO_WORLD_HPP
#define PHRO_WORLD_HPP

#include <SFML/Graphics.hpp>

#include <memory>
using namespace std;

#include "../phro_data.hpp"
#include "../structures/phro_scene_node.hpp"
#include "../structures/phro_sprite_node.hpp"
#include "phro_character.hpp"

class World : private sf::NonCopyable
{
	enum Layer
	{
		Background,
		Surface,
		LayerCount
	};
	
public:
	
	World(Data* gameData);
	void update(float dt);
	void draw();
	void resizeView();
	
private:
	
	void loadTextures();
	void buildScene();
	
	Data* data;
	sf::View worldView;
	SceneNode sceneGraph;
	std::array<SceneNode*, LayerCount> sceneLayers;
	sf::FloatRect worldBounds;
	sf::Vector2f spawnPosition;
	float scrollSpeed;
	Character* playerCharacter;
};

#endif // PHRO_WORLD_HPP
