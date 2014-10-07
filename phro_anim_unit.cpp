/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#include <iostream>
using namespace std;

#include "phro_anim_unit.hpp"

void AnimUnit::loadAnimation(const string& name, const sf::Texture& texture, const string& fileDirectory)
{
	string infoAdress = fileDirectory + "/" + name + ".frame";
	
	frameInfo.readFile(infoAdress);
	
	//animSprite.setTexture(texture);
	//animSprite.setPosition(100.f, 100.f);
	//animSprite.setTextureRect(frameInfo.getFrameRect(frameInfo.defaultFrame()));
	
	/*int count = 0;
	for(auto mtype : frameInfo.modeType)
	{
		cout << "For " << mtype.first << ":\n";
		thor::FrameAnimation animFrame;
		for(int i = 0; i < mtype.second.size(); i++)
		{
			animFrame.addFrame(1.f, frameInfo.getFrameRect(mtype.second[i]));
			cout << "  adding frame " << mtype.second[i] << endl;
		}
		
		animFrames.push_back(animFrame);
		animator.addAnimation(mtype.first, animFrames[count], sf::seconds(1.f));
		cout << endl;
		count++;
	}*/
	
	/*aProgress = 0.f;
	cout << "For " << "walk" << ":\n";
	for(int i = 0; i < frameInfo.modeType["walk"].size(); i++)
	{
		animFrame.addFrame(1.f, frameInfo.getFrameRect(frameInfo.modeType["walk"][i]));
		cout << "  adding frame " << frameInfo.modeType["walk"][i] << endl;
	}
	animFrame(animSprite, aProgress);*/
	
	for(int i = 0; i < frameInfo.modeType["default"].size(); i++)
		adefault.addFrame(1.f, frameInfo.getFrameRect(frameInfo.modeType["default"][i]));
	for(int i = 0; i < frameInfo.modeType["walk"].size(); i++)
		walk.addFrame(1.f, frameInfo.getFrameRect(frameInfo.modeType["walk"][i]));
	for(int i = 0; i < frameInfo.modeType["jump"].size(); i++)
		jump.addFrame(1.f, frameInfo.getFrameRect(frameInfo.modeType["jump"][i]));
	for(int i = 0; i < frameInfo.modeType["fall"].size(); i++)
		fall.addFrame(1.f, frameInfo.getFrameRect(frameInfo.modeType["fall"][i]));
	
	animator.addAnimation("default", adefault, sf::seconds(1.f));
	animator.addAnimation("walk", walk, sf::seconds(1.f));
	animator.addAnimation("jump", jump, sf::seconds(1.f));
	animator.addAnimation("fall", fall, sf::seconds(1.f));
}

void AnimUnit::update(float dt)
{
	if (!animator.isPlayingAnimation())
		animator.playAnimation("default");
	
	animator.update(sf::seconds(dt));
	
	//aProgress += dt / 1.f;
	//if (aProgress > 1.f)
	//	aProgress = 0.f;
}

void AnimUnit::animate(sf::Sprite& animSprite)
{
	animator.animate(animSprite);
}

void AnimUnit::play(const string& modeName)
{
	animator.playAnimation(modeName, true);
}

sf::Sprite& AnimUnit::show()
{
	//return animSprite;
}
