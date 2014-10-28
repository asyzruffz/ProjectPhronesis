/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#ifndef PHRO_SECTION_HPP
#define PHRO_SECTION_HPP

#include <string>
#include <vector>
using namespace std;

#include <SFML/Graphics.hpp>

#include "../resourceshandling/phro_resource_manager.hpp"
#include "phro_tile.hpp"

class Section
{
public:
	
	Section(){}
	Section(int mwidth, int mheight, const string& filename);
	
	void draw(sf::RenderWindow& window);
	void acquireResource(ResourceManager* source);
	
private:
	
	void updateTileVariant();
	
	vector<Tile> tiles;
	int width;
    int height;
	ResourceManager* rsc;
};

#endif // PHRO_SECTION_HPP
