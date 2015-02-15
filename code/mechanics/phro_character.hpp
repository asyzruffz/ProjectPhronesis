/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#ifndef PHRO_CHARACTER_HPP
#define PHRO_CHARACTER_HPP

#include <SFML/Graphics.hpp>

#include <string>
using namespace std;

#include "../structures/phro_entity.hpp"
#include "../resourceshandling/phro_animation_manager.hpp"

class Character : public Entity
{
public:
	
	Character(string type = "", AnimationManager* animHolder = nullptr): cType(type), animHolder(animHolder) {}
	void setCharacter(string type, AnimationManager* animHoldr);
	
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	
private:
	
	string cType;
	AnimationManager* animHolder;
};

#endif // PHRO_CHARACTER_HPP
