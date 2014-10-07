/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#ifndef PHRO_ANIMATION_MANAGER_HPP
#define PHRO_ANIMATION_MANAGER_HPP

#include <string>
#include <map>
using namespace std;

#include "phro_resource_manager.hpp"
#include "phro_anim_unit.hpp"

class AnimationManager
{
public:

	AnimationManager(){}
	AnimationManager(ResourceManager* rscMgr);

	void addAnim(string name, string fileDirectory);
	void updateAll(float dt);

	//Resources stored here
	map<string, AnimUnit> animCollection;

private:

	ResourceManager* textureSource;
};

#endif // PHRO_ANIMATION_MANAGER_HPP
