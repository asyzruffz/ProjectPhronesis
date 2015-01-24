/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#include "phro_world.hpp"

World::World(Data* gameData): data(gameData),
							worldView(data->window.getDefaultView()), 
							worldBounds( 0.f, 0.f, // left X position, top Y position
										worldView.getSize().x * 2.f, worldView.getSize().y * 2.f ), // width, height
							spawnPosition( worldView.getSize().x / 2.f, worldView.getSize().y / 2.f ),
							playerCharacter(nullptr)
{
	loadTextures();
	buildScene();
	worldView.setCenter(spawnPosition);
}

void World::loadTextures()
{
	data->rscStorage.loadTexture("land", "assets/tiles/dirt/dirtTile00.png");
}

void World::buildScene()
{
	for (int i = 0; i < LayerCount; i++)
	{
		SceneNode::Ptr layer(new SceneNode());
		sceneLayers[i] = layer.get();
		sceneGraph.attachChild(std::move(layer));
	}
	
	sf::Texture& texture = data->rscStorage.getTextureRef("land");
	sf::IntRect textureRect(worldBounds);
	texture.setRepeated(true);
	
	unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(worldBounds.left, worldBounds.top);
	sceneLayers[Background]->attachChild(std::move(backgroundSprite));
	
	unique_ptr<Character> leader(new Character("greenalien", &data->animStorage));
	playerCharacter = leader.get();
	playerCharacter->setPosition(spawnPosition);
	playerCharacter->setVelocity(40.f, scrollSpeed);
	sceneLayers[Air]->attachChild(std::move(leader));
}

void World::update(float dt)
{
	//worldView.move(0.f, scrollSpeed * dt);
	
	sf::Vector2f position = playerCharacter->getPosition();
	sf::Vector2f velocity = playerCharacter->getVelocity();
	sf::Vector2f scale = playerCharacter->getScale();
	
	worldView.setCenter(position);
	
	if (position.x <= worldBounds.left + 150 || position.x >= worldBounds.left + worldBounds.width - 150)
	{
		velocity.x = -velocity.x;
		scale.x = -scale.x;
		playerCharacter->setVelocity(velocity);
		playerCharacter->setScale(scale);
	}
	
	sceneGraph.update(dt);
}

void World::draw()
{
	data->window.setView(worldView);
	data->window.draw(sceneGraph);
}

void World::resizeView()
{
	worldView.setSize(sf::Vector2f(data->window.getSize()));
}
