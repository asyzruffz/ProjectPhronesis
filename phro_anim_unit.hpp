/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#ifndef PHRO_ANIM_UNIT_HPP
#define PHRO_ANIM_UNIT_HPP

#include <string>
#include <vector>
using namespace std;

#include <SFML/Graphics.hpp>
#include <Thor/Animation.hpp>

#include "phro_frame_info.hpp"

class AnimUnit
{
public:
	
	AnimUnit(){}
	
	//Load from a file
	void loadAnimation(const string& name, const sf::Texture& texture, const string& fileDirectory);
	
	void update(float dt);
	void animate(sf::Sprite& animSprite);
	void play(const string& modeName);
	
	sf::Sprite& show();
	
private:
	
	FrameInfo frameInfo;
	vector<thor::FrameAnimation> animFrames;
	thor::Animator<sf::Sprite, string> animator;
	thor::FrameAnimation adefault;
	thor::FrameAnimation walk;
	thor::FrameAnimation jump;
	thor::FrameAnimation fall;
	//float aProgress;
};

#endif // PHRO_ANIM_UNIT_HPP
