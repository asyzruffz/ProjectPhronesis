/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#include <iostream>
using namespace std;

#include "phro_anim_unit.hpp"

AnimUnit::AnimUnit(const string& name, const sf::Texture& texture, const string& fileDirectory)
{
	unitName = name;
	string infoAdress = fileDirectory + "/" + unitName + ".frame";
	
	frameInfo.readFile(infoAdress);
	
	animSprite.setTexture(texture);
	
	loop = true;
	playing = false;
	animTimer = 0.f;
	animPosition = 0;
	currentMode = "default";
	animSprite.setTextureRect(frameInfo.getFrameRect(frameInfo.defaultFrame()));
	sf::Vector2f fsize(frameInfo.frameSize);
	animSprite.setOrigin(fsize.x * 0.5, fsize.y * 0.5);
	isClicked = false;
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
		cout << "Animation Error: There is no [" << modeName << "] for " << unitName << endl;
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

bool AnimUnit::clicked(sf::Vector2i& cursorPos, bool holding)
{
	string pressed, hover;
	if(frameInfo.modeType.count("pressed") == 1)
		pressed = "pressed";
	else
		pressed = "default";
	if(frameInfo.modeType.count("hover") == 1)
		hover = "hover";
	else
		hover = "default";
	
	if(contains(cursorPos))
	{
		if(isClicked && (holding || !sf::Mouse::isButtonPressed(sf::Mouse::Left)))
		{
			isClicked = false;
			return true;
		}
		
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			isClicked = true;
			play(pressed);
		}
		else
			play(hover);
	}
	else
		play("default");
	
	return false;
}

bool AnimUnit::contains(sf::Vector2i& point)
{
	sf::Transform trans = getTransform();
	sf::FloatRect spriteBounds = animSprite.getGlobalBounds();
	spriteBounds = trans.transformRect(spriteBounds);
	return spriteBounds.contains(sf::Vector2f(point));
}
