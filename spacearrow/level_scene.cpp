/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#include "level_scene.hpp"

#include "game_data.hpp"
#include "game_object_2d.hpp"
#include "transform_2d.hpp"
#include "sprite.hpp"
#include "rigidbody_2d.hpp"

void LevelScene::hierarchy()
{
	// Creating game objects
	GameObject2D* a = new GameObject2D("Alien");
	a->addComponent<Sprite>("alien");
	a->addComponent<Rigidbody2D>(true);
	GameObject2D* b = new GameObject2D("Box");
	b->addComponent<Rigidbody2D>(true);
	GameObject2D* c = new GameObject2D("Platform");
	c->addComponent<Rigidbody2D>(false);

	// Initializing game objects' values
	//Rigidbody2D::setGravity(sf::Vector2f(0, 0));
	a->getComponent<Sprite>().setSpriteAnchor(sf::Vector2f(0.5f, 0.5f));
	a->getComponent<Transform2D>().setPosition(sf::Vector2f(2, 1));
	a->getComponent<Transform2D>().setRotation(-30);
	b->getComponent<Transform2D>().setPosition(sf::Vector2f(4, 1));
	b->getComponent<Transform2D>().setRotation(30);
	c->getComponent<Transform2D>().setPosition(sf::Vector2f(4, 8));
	c->getComponent<Transform2D>().setScale(sf::Vector2f(6, 1));

	// Add to hierarchy root
	addToRoot(a);
	addToRoot(b);
	addToRoot(c);
}