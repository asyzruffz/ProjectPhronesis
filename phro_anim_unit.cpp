/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#include <iostream>
using namespace std;

#include "phro_anim_unit.hpp"

AnimUnit::AnimUnit(const string& name, const sf::Texture& texture, const string& fileDirectory)
{
	string infoAdress = fileDirectory + "/" + name + ".frame";
	
	frameInfo.readFile(infoAdress);
	
	animSprite.setTexture(texture);
	
	loop = true;
	playing = false;
	animTimer = 0.f;
	animPosition = 0;
	currentMode = "default";
	animSprite.setTextureRect(frameInfo.getFrameRect(frameInfo.defaultFrame()));
	
}

void AnimUnit::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(animSprite, states);
}

void AnimUnit::update(float dt)
{
	if(!playing) return;
	
	animTimer += dt;
	
	if(animTimer > frameInfo.frameDelay)
	{
		animTimer -= frameInfo.frameDelay;
		animPosition++;
	}
	
	if(animPosition >= frameInfo.modeType[currentMode].size())
	{
		animPosition = 0;
		if(!loop)
			stop();
	}
	
	animSprite.setTextureRect(frameInfo.getFrameRect(frameInfo.modeType[currentMode][animPosition]));
}

void AnimUnit::play(const string& modeName, bool looping)
{
	loop = looping;
	
	if(currentMode != modeName)
	{
		animTimer = 0.f;
		animPosition = 0;
	}
	
	if(frameInfo.modeType.count(modeName) != 1)
	{
		playing = false;
		cout << "Animation Error: There is no [" << modeName << "]" << endl;
	}
	else
	{
		currentMode = modeName;
		playing = true;
	}
}

void AnimUnit::stop()
{
	playing = false;
}

bool AnimUnit::isPlaying()
{
	return playing;
}

bool AnimUnit::contains(sf::Vector2i& point)
{
	sf::Transform trans = getTransform();
	sf::FloatRect spriteBounds = animSprite.getGlobalBounds();
	spriteBounds = trans.transformRect(spriteBounds);
	return spriteBounds.contains(sf::Vector2f(point));
}
