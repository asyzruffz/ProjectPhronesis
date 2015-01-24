/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#include "phro_character.hpp"

void Character::setCharacter(string type, AnimationManager* animHoldr)
{
	cType = type;
	animHolder = animHoldr;
}

void Character::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(cType == "")
		return; // place generic box drawing here
	
	if(animHolder != nullptr)
		target.draw(animHolder->animList[cType], states);
}
