/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#ifndef GAME_DATA_HPP
#define GAME_DATA_HPP

#include <SFML/Graphics.hpp>

//#include "resourceshandling/phro_resource_manager.hpp"
//#include "resourceshandling/phro_animation_manager.hpp"

// A game data class that is a singleton so that it only has one instance
// Its members can also be accessed from anywhere or from any state.

class GameData
{
private:

	GameData() {}

public:

	static GameData& instance()
	{
		static GameData inst;// Guaranteed to be destroyed. Instantiated on first use.
		return inst;
	}

	// Deleting the methods otherwise you may accidentally get copies of
    // your singleton appearing.
	GameData(GameData const&) = delete;
	void operator=(GameData const&) = delete;

	sf::RenderWindow window;
	//ResourceManager rscStorage;
	//AnimationManager animStorage;

};

#endif // GAME_DATA_HPP
