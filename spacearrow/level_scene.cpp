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
#include "player_controller.hpp"
#include "object_spawner.hpp"
#include "gravitational_attraction.hpp"
#include "portal.hpp"
#include "test_script.hpp"

void LevelScene::hierarchy()
{
	Rigidbody2D::setGravity(sf::Vector2f(0, 0));

	// Creating game objects ----------------------

	// Background
	GameObject2D* newObject = new GameObject2D("Background");
	newObject->addComponent<Sprite>("background");
	newObject->getComponent<Sprite>().setSpriteAnchor(sf::Vector2f(0, 0));
	addToRoot(newObject);

	// Asteroids
	for (int i = 1; i <= 2; i++)
	{
		newObject = new GameObject2D("Asteroid" + to_string(i));
		newObject->addComponent<Sprite>("asteroid" + to_string(i));
		newObject->addComponent<Rigidbody2D>(BodyType::Static, BodyShapeType::Circle);
		newObject->getComponent<Transform2D>().setPosition(sf::Vector2f(10.0f * i, 15.0f));

		GameObject2D* sensor = new GameObject2D("GravityRange");
		sensor->addComponent<Sprite>("ring");
		sensor->addComponent<Rigidbody2D>(BodyType::Static, BodyShapeType::Circle);
		sensor->addComponent<GravitationalAttraction>(2.0f);
		//sensor->getComponent<Transform2D>().setScale(sf::Vector2f(7, 7));
		sensor->getComponent<Rigidbody2D>().setIsTrigger(true);
		sensor->setParent(newObject);

		addToRoot(newObject);
	}

	// Wormhole

	GameObject2D* hole = new GameObject2D("Hole");
	hole->addComponent<Rigidbody2D>(BodyType::Static, BodyShapeType::Circle);
	hole->getComponent<Transform2D>().setScale(sf::Vector2f(2, 2));
	hole->getComponent<Rigidbody2D>().setIsTrigger(true);
	//hole->getComponent<Rigidbody2D>().setDrawBody(true);

	GameObject2D* hole2 = new GameObject2D("Hole");
	hole2->addComponent<Rigidbody2D>(BodyType::Static, BodyShapeType::Circle);
	hole2->getComponent<Transform2D>().setScale(sf::Vector2f(2, 2));
	hole2->getComponent<Rigidbody2D>().setIsTrigger(true);
	//hole2->getComponent<Rigidbody2D>().setDrawBody(true);

	hole->addComponent<Portal>(hole2);
	hole2->addComponent<Portal>(hole);

	newObject = new GameObject2D("Wormhole 1");
	newObject->addComponent<Sprite>("wormhole");
	newObject->addComponent<Rigidbody2D>(BodyType::Static, BodyShapeType::Circle);
	newObject->getComponent<Transform2D>().setPosition(sf::Vector2f(10.0f, 5.0f));
	newObject->getComponent<Rigidbody2D>().setIsTrigger(true);

	hole->setParent(newObject);
	addToRoot(newObject);

	newObject = new GameObject2D("Wormhole 2");
	newObject->addComponent<Sprite>("wormhole");
	newObject->addComponent<Rigidbody2D>(BodyType::Static, BodyShapeType::Circle);
	newObject->getComponent<Transform2D>().setPosition(sf::Vector2f(20.0f, 10.0f));
	newObject->getComponent<Rigidbody2D>().setIsTrigger(true);

	hole2->setParent(newObject);
	addToRoot(newObject);

	// Bullet
	GameObject2D bullet("Bullet");
	bullet.addComponent<Rigidbody2D>(BodyType::Dynamic);
	bullet.getComponent<Transform2D>().setScale(sf::Vector2f(0.2f, 0.5f));
	bullet.getComponent<Rigidbody2D>().setDrawBody(true);

	// Player
	newObject = new GameObject2D("Player");
	newObject->addComponent<Sprite>("player");
	newObject->addComponent<Rigidbody2D>(BodyType::Dynamic, BodyShapeType::Circle);
	newObject->addComponent<PlayerController>();
	newObject->addComponent<ObjectSpawner>(&bullet);
	newObject->getComponent<Transform2D>().setPosition(sf::Vector2f(10, 10));
	newObject->getComponent<Transform2D>().setRotation(90);
	addToRoot(newObject);

	// Enemy
	newObject = new GameObject2D("Enemy");
	newObject->addComponent<Sprite>("enemy1");
	newObject->addComponent<Rigidbody2D>(BodyType::Dynamic, BodyShapeType::Circle);
	newObject->getComponent<Transform2D>().setPosition(sf::Vector2f(18, 20));
	addToRoot(newObject);


	/*GameObject2D* a = new GameObject2D("Alien");
	a->addComponent<Sprite>("alien");
	a->addComponent<Rigidbody2D>(BodyType::Dynamic);
	a->addComponent<TestScript>();
	a->getComponent<Transform2D>().setPosition(sf::Vector2f(2, 1));
	a->getComponent<Transform2D>().setRotation(-30);
	addToRoot(a);

	GameObject2D* b = new GameObject2D("Box");
	b->addComponent<Rigidbody2D>(BodyType::Dynamic);
	b->getComponent<Transform2D>().setPosition(sf::Vector2f(4, 1));
	b->getComponent<Transform2D>().setRotation(30);
	b->getComponent<Rigidbody2D>().setDrawBody(true);

	GameObject2D* b2 = new GameObject2D("BoxChild");
	b2->addComponent<Rigidbody2D>(BodyType::Kinematic);
	b2->addComponent<Sprite>("alien");
	b2->getComponent<Transform2D>().setPosition(sf::Vector2f(2, 1));
	b2->setParent(b);

	addToRoot(b);

	GameObject2D* c = new GameObject2D("Platform");
	c->addComponent<Rigidbody2D>(BodyType::Static);
	c->addComponent<TestScript>();
	c->getComponent<Transform2D>().setPosition(sf::Vector2f(4, 8));
	c->getComponent<Transform2D>().setScale(sf::Vector2f(6, 1));
	c->getComponent<Rigidbody2D>().setDrawBody(true);
	addToRoot(c);*/
}
