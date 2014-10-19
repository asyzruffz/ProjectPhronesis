/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#ifndef PHRO_ANIM_UNIT_HPP
#define PHRO_ANIM_UNIT_HPP

#include <string>
using namespace std;

#include <SFML/Graphics.hpp>

#include "phro_frame_info.hpp"

class AnimUnit : public sf::Drawable
{
public:
	
	AnimUnit(){}
	//Load from a file
	AnimUnit(const string& name, const sf::Texture& texture, const string& fileDirectory);
	
	void update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	void play(const string& modeName, bool looping = true);
	void stop();
	bool isPlaying();
	
private:
	
	FrameInfo frameInfo;
	sf::Sprite animSprite;
	string currentMode;
	float animTimer;
	int animPosition;
	bool playing;
	bool loop;
};

#endif // PHRO_ANIM_UNIT_HPP
