/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#ifndef SCENE_HPP
#define SCENE_HPP

#include <Box2D/Box2D.h>

#include <memory>
using namespace std;

#include "game_object.hpp"
#include "contact_listener_2d.hpp"

// Forward declaration to avoid cyclic dependency
class SceneHandler;

class Scene
{
public:
	
	Scene(SceneHandler* handler);
	virtual ~Scene() {}

	typedef unique_ptr<Scene> Ptr;

	virtual void hierarchy() = 0;

	virtual void start();
	virtual void handleEvent();
	virtual void update(float dt);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	void addToRoot(GameObject* gameObject);

	static b2World world;

protected:
	
	void requestSceneChange(const int& sceneIndex);
	void requestSceneClear();
	
	SceneHandler* mp_handler;

private:

	Entity::Ptr mp_root;
	float m_fixedTimeStep;
	float m_timeElapsed;

	static ContactListener2D contactListenerInstance;
};

#endif // SCENE_HPP
