/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#include "level_scene.hpp"

#include "game_object_2d.hpp"
#include "transform_2d.hpp"
#include "camera_2d.hpp"
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

	// Camera
	GameObject2D* cam = new GameObject2D("Camera");
	cam->addComponent<Camera2D>();
	cam->getComponent<Transform2D>().setScale(sf::Vector2f(2.0f, 2.0f));
	addToRoot(cam);

	// Background
	GameObject2D* newObject = new GameObject2D("Background");
	newObject->addComponent<Sprite>("background");
	newObject->getComponent<Transform2D>().setScale(sf::Vector2f(2.0f, 2.0f));
	addToRoot(newObject);

	// Asteroids

	newObject = new GameObject2D("Asteroid1");
	newObject->addComponent<Sprite>("asteroid1");
	newObject->addComponent<Rigidbody2D>(BodyType::Static, BodyShapeType::Circle);
	newObject->getComponent<Transform2D>().setPosition(sf::Vector2f(-30.0f, -10.0f));
	newObject->getComponent<Rigidbody2D>().setRestitution(1.0f);
	addToRoot(newObject);

	newObject = new GameObject2D("Asteroid2");
	newObject->addComponent<Sprite>("asteroid2");
	newObject->addComponent<Rigidbody2D>(BodyType::Static, BodyShapeType::Circle);
	newObject->getComponent<Transform2D>().setPosition(sf::Vector2f(15.0f, -20.0f));
	newObject->getComponent<Rigidbody2D>().setRestitution(1.0f);
	addToRoot(newObject);

	newObject = new GameObject2D("Asteroid3");
	newObject->addComponent<Sprite>("asteroid3");
	newObject->addComponent<Rigidbody2D>(BodyType::Static, BodyShapeType::Circle);
	newObject->getComponent<Transform2D>().setPosition(sf::Vector2f(-17.0f, 18.0f));
	newObject->getComponent<Rigidbody2D>().setRestitution(1.0f);
	addToRoot(newObject);

	newObject = new GameObject2D("Asteroid4");
	newObject->addComponent<Sprite>("asteroid4");
	newObject->addComponent<Rigidbody2D>(BodyType::Static, BodyShapeType::Circle);
	newObject->getComponent<Transform2D>().setPosition(sf::Vector2f(23.0f, 10.0f));
	newObject->getComponent<Rigidbody2D>().setRestitution(1.0f);
	addToRoot(newObject);

	// Wormhole

	GameObject2D* hole = new GameObject2D("Hole");
	hole->addComponent<Rigidbody2D>(BodyType::Static, BodyShapeType::Circle);
	hole->getComponent<Transform2D>().setScale(sf::Vector2f(2.0f, 2.0f));
	hole->getComponent<Rigidbody2D>().setIsTrigger(true);

	GameObject2D* hole2 = new GameObject2D("Hole");
	hole2->addComponent<Rigidbody2D>(BodyType::Static, BodyShapeType::Circle);
	hole2->getComponent<Transform2D>().setScale(sf::Vector2f(2.0f, 2.0f));
	hole2->getComponent<Rigidbody2D>().setIsTrigger(true);

	hole->addComponent<Portal>(hole2);
	hole2->addComponent<Portal>(hole);

	newObject = new GameObject2D("Wormhole1");
	newObject->addComponent<Sprite>("wormhole");
	newObject->addComponent<Rigidbody2D>(BodyType::Static, BodyShapeType::Circle);
	newObject->getComponent<Transform2D>().setPosition(sf::Vector2f(-25.0f, 5.0f));
	newObject->getComponent<Rigidbody2D>().setIsTrigger(true);

	hole->setParent(newObject);
	addToRoot(newObject);

	newObject = new GameObject2D("Wormhole2");
	newObject->addComponent<Sprite>("wormhole");
	newObject->addComponent<Rigidbody2D>(BodyType::Static, BodyShapeType::Circle);
	newObject->getComponent<Transform2D>().setPosition(sf::Vector2f(20.0f, -10.0f));
	newObject->getComponent<Transform2D>().setRotation(-20.0f);
	newObject->getComponent<Rigidbody2D>().setIsTrigger(true);

	hole2->setParent(newObject);
	addToRoot(newObject);

	// Planet
	newObject = new GameObject2D("Planet");
	newObject->addComponent<Sprite>("venus");
	newObject->addComponent<Rigidbody2D>(BodyType::Static, BodyShapeType::Circle);

	GameObject2D* sensor = new GameObject2D("GravityRange");
	sensor->addComponent<Sprite>("ring");
	sensor->addComponent<Rigidbody2D>(BodyType::Static, BodyShapeType::Circle);
	sensor->addComponent<GravitationalAttraction>(2.0f);
	sensor->getComponent<Transform2D>().setScale(sf::Vector2f(2.0f, 2.0f));
	sensor->getComponent<Rigidbody2D>().setIsTrigger(true);
	sensor->setParent(newObject);

	addToRoot(newObject);

	// Bullet
	GameObject2D bullet("Bullet");
	bullet.addComponent<Sprite>("missile");
	bullet.addComponent<Rigidbody2D>(BodyType::Dynamic);
	bullet.getComponent<Transform2D>().setScale(sf::Vector2f(0.6f, 0.6f));
	bullet.getComponent<Rigidbody2D>().setDrawBody(true);

	// Player
	newObject = new GameObject2D("Player");
	newObject->addComponent<Sprite>("player");
	newObject->addComponent<Rigidbody2D>(BodyType::Kinematic, BodyShapeType::Circle);
	newObject->addComponent<PlayerController>();
	newObject->addComponent<ObjectSpawner>(&bullet);
	newObject->getComponent<Transform2D>().setPosition(sf::Vector2f(-20.0f, -15.0f));
	newObject->getComponent<Transform2D>().setRotation(90.0f);
	addToRoot(newObject);

	//cam->getComponent<Camera2D>().setTarget(newObject);

	// Enemy
	newObject = new GameObject2D("Enemy");
	newObject->addComponent<Sprite>("enemy1");
	newObject->addComponent<Rigidbody2D>(BodyType::Dynamic, BodyShapeType::Circle);
	newObject->getComponent<Transform2D>().setPosition(sf::Vector2f(5.0f, 20.0f));
	addToRoot(newObject);

	newObject = new GameObject2D("Building1");
	newObject->addComponent<Sprite>("building");
	newObject->addComponent<Rigidbody2D>(BodyType::Dynamic, BodyShapeType::Box);
	newObject->getComponent<Transform2D>().setPosition(sf::Vector2f(11.0f, 0.0f));
	newObject->getComponent<Transform2D>().setRotation(90.0f);
	newObject->getComponent<Transform2D>().setScale(sf::Vector2f(0.2f, 0.2f));
	addToRoot(newObject);

	newObject = new GameObject2D("Building2");
	newObject->addComponent<Sprite>("building");
	newObject->addComponent<Rigidbody2D>(BodyType::Dynamic, BodyShapeType::Box);
	newObject->getComponent<Transform2D>().setPosition(sf::Vector2f(0.0f, 11.0f));
	newObject->getComponent<Transform2D>().setRotation(180.0f);
	newObject->getComponent<Transform2D>().setScale(sf::Vector2f(0.2f, 0.2f));
	addToRoot(newObject);

	newObject = new GameObject2D("Building3");
	newObject->addComponent<Sprite>("building");
	newObject->addComponent<Rigidbody2D>(BodyType::Dynamic, BodyShapeType::Box);
	newObject->getComponent<Transform2D>().setPosition(sf::Vector2f(8.0f, 8.0f));
	newObject->getComponent<Transform2D>().setRotation(135.0f);
	newObject->getComponent<Transform2D>().setScale(sf::Vector2f(0.2f, 0.2f));
	addToRoot(newObject);

	newObject = new GameObject2D("Building4");
	newObject->addComponent<Sprite>("building");
	newObject->addComponent<Rigidbody2D>(BodyType::Dynamic, BodyShapeType::Box);
	newObject->getComponent<Transform2D>().setPosition(sf::Vector2f(10.0f, -5.0f));
	newObject->getComponent<Transform2D>().setRotation(60.0f);
	newObject->getComponent<Transform2D>().setScale(sf::Vector2f(0.2f, 0.2f));
	addToRoot(newObject);

	// Invisible Walls

	newObject = new GameObject2D("WallLeft");
	newObject->addComponent<Rigidbody2D>(BodyType::Static);
	newObject->getComponent<Transform2D>().setPosition(sf::Vector2f(-33.0f, 0.0f));
	newObject->getComponent<Transform2D>().setScale(sf::Vector2f(1.0f, 50.0f));
	//newObject->getComponent<Rigidbody2D>().setDrawBody(true);
	addToRoot(newObject);

	newObject = new GameObject2D("WallRight");
	newObject->addComponent<Rigidbody2D>(BodyType::Static);
	newObject->getComponent<Transform2D>().setPosition(sf::Vector2f(33.0f, 0.0f));
	newObject->getComponent<Transform2D>().setScale(sf::Vector2f(1.0f, 50.0f));
	//newObject->getComponent<Rigidbody2D>().setDrawBody(true);
	addToRoot(newObject);

	newObject = new GameObject2D("WallTop");
	newObject->addComponent<Rigidbody2D>(BodyType::Static);
	newObject->getComponent<Transform2D>().setPosition(sf::Vector2f(0.0f, -25.0f));
	newObject->getComponent<Transform2D>().setScale(sf::Vector2f(67.0f, 1.0f));
	//newObject->getComponent<Rigidbody2D>().setDrawBody(true);
	addToRoot(newObject);

	newObject = new GameObject2D("WallBottom");
	newObject->addComponent<Rigidbody2D>(BodyType::Static);
	newObject->getComponent<Transform2D>().setPosition(sf::Vector2f(0.0f, 25.0f));
	newObject->getComponent<Transform2D>().setScale(sf::Vector2f(67.0f, 1.0f));
	//newObject->getComponent<Rigidbody2D>().setDrawBody(true);
	addToRoot(newObject);
}
