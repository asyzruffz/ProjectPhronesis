/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#include "phro_animation_manager.hpp"

AnimationManager::AnimationManager(ResourceManager* rscMgr)
: textureSource(rscMgr) {}

void AnimationManager::addAnim(string name, string fileDirectory)
{
	AnimUnit newAnim;
	newAnim.loadAnimation(name, textureSource->getTextureRef(name), fileDirectory);

	animCollection[name] = newAnim;
}

void AnimationManager::updateAll(float dt)
{
	for(auto animObject : animCollection)
		animObject.second.update(dt);
}
