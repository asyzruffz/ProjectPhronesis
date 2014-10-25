/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#include "phro_section.hpp"

Section::Section(int mwidth, int mheight) : width(mwidth), height(mheight)
{
	for(int i = 0; i < (width * height); i++)
	{
		tiles.push_back(Tile(TileName::DIRT, TileType::FLOOR));
	}
}

void Section::draw(sf::RenderWindow& window)
{
	
}

void Section::updateTileVariant(TileType tileType)
{
	
}
