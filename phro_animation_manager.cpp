/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#include "phro_animation_manager.hpp"

AnimationManager::AnimationManager(ResourceManager* rscMgr)
: textureSource(rscMgr) {}

void AnimationManager::addAnim(string name, string fileDirectory)
{
	animList[name] = AnimUnit(name, textureSource->getTextureRef(name), fileDirectory);
}

void AnimationManager::updateAll(float dt)
{
	for(map<string, AnimUnit>::iterator it = animList.begin(); it != animList.end(); it++)
		it->second.update(dt);
}
