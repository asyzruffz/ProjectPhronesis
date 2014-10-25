/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#include "phro_tile.hpp"

string tileNameToStr(TileType type)
{
	switch(type)
    {
        default:
        case TileType::VOID:				return "void";
        case TileType::DIRT:				return "dirt";
        case TileType::GRASS:				return "grass";
        case TileType::LAKE:				return "lake";
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
