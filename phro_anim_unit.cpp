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
	animSprite.setPosition(100.f, 100.f);
	
	animTimer = 0.f;
	currentMode = "default";
	animSprite.setTextureRect(frameInfo.getFrameRect(frameInfo.defaultFrame()));
	
	/*for(auto mtype : frameInfo.modeType)
	{
		cout << "For " << mtype.first << ":\n";
		thor::FrameAnimation animFrame;
		for(int i = 0; i < mtype.second.size(); i++)
		{
			animFrame.addFrame(1.f, frameInfo.getFrameRect(mtype.second[i]));
			cout << "  adding frame " << mtype.second[i] << endl;
		}
		
		animator.addAnimation(mtype.first, animFrame, sf::seconds(1.f));
		cout << endl;
	}*/
	
}

void AnimUnit::update(float dt)
{
	animTimer += dt;
	
	if(animTimer >= frameInfo.modeType[currentMode].size())
		animTimer = 0.f;
	else
		animSprite.setTextureRect(frameInfo.getFrameRect(frameInfo.modeType[currentMode][floor(animTimer)]));
	
}

void AnimUnit::play(const string& modeName)
{
	currentMode = modeName;
}

sf::Sprite& AnimUnit::show()
{
	return animSprite;
}
