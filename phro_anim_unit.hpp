/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#ifndef PHRO_ANIM_UNIT_HPP
#define PHRO_ANIM_UNIT_HPP

#include <string>
#include <vector>
#include <cmath>
using namespace std;

#include <SFML/Graphics.hpp>
#include <Thor/Animation.hpp>

#include "phro_frame_info.hpp"

class AnimUnit
{
public:
	
	AnimUnit(){}
	//Load from a file
	AnimUnit(const string& name, const sf::Texture& texture, const string& fileDirectory);
	
	void update(float dt);
	void play(const string& modeName);
	
	sf::Sprite& show();
	
private:
	
	FrameInfo frameInfo;
	sf::Sprite animSprite;
	string currentMode;
	float animTimer;
};

#endif // PHRO_ANIM_UNIT_HPP
