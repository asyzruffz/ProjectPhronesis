/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#ifndef PHRO_SECTION_HPP
#define PHRO_SECTION_HPP

#include <vector>
using namespace std;

#include <SFML/Graphics.hpp>

#include "phro_tile.hpp"

class Section
{
public:
	
	Section(){}
	Section(int mwidth, int mheight);
	
	void draw(sf::RenderWindow& window);
	
private:
	
	void updateTileVariant(TileType tileType);
	
	vector<Tile> tiles;
	int width;
    int height;
};

#endif // PHRO_SECTION_HPP
