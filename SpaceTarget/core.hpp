/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#ifndef CORE_HPP
#define CORE_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "scene_handler.hpp"

// The core of the game handling all of the states

class Core
{
public:

	Core(string gameTitle = "Untitled");

	void run();				// main loop

	void inputHandling();						// The big 3 functions
	void update(float dt);						// running in a loop
	void draw(sf::RenderWindow& window) const;		//

	void loadResources();

	void registerScenes();

private:

	sf::RenderWindow m_window;
	sf::RenderStates m_renderStates;
	SceneHandler m_scenes;
};

#endif // CORE_HPP
