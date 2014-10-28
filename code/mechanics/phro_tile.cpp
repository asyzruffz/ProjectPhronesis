/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#include "phro_tile.hpp"

string tileNameToStr(TileName name)
{
	switch(name)
    {
        default:
        case TileName::VOID:	return "void";
        case TileName::DIRT:	return "dirt";
        case TileName::GRASS:	return "grass";
        case TileName::LAKE:	return "lake";
	}
}

TileName intTotileName(int name)
{
	switch(name)
    {
        default:
        case 0:		return TileName::VOID;
        case 1:		return TileName::DIRT;
        case 2:		return TileName::GRASS;
        case 3:		return TileName::LAKE;
	}
}

Tile::Tile(const TileName mtileName, const TileType mtileType)
{
	tileName = mtileName;
	tileType = mtileType;
	tileVariant = 0;
}

void Tile::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Tile::update(float dt)
{
	
}

void Tile::setTileVariant(int variant)
{
	tileVariant = variant;
}

int Tile::getTileVariant()
{
	return tileVariant;
}
