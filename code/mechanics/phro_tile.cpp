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

void Tile::update()
{
	if((nbrInfo.getVar(0) == 2 || nbrInfo.getVar(0) == 6) && (nbrInfo.getVar(1) == 1 || nbrInfo.getVar(1) == 6) &&
			tileName == nbrInfo.getName(0) && tileName == nbrInfo.getName(1))
		setTileVariant(9);
	else if((nbrInfo.getVar(1) == 3 || nbrInfo.getVar(1) == 7) && (nbrInfo.getVar(2) == 2 || nbrInfo.getVar(2) == 7) &&
			tileName == nbrInfo.getName(1) && tileName == nbrInfo.getName(2))
		setTileVariant(10);
	else if((nbrInfo.getVar(2) == 4 || nbrInfo.getVar(2) == 8) && (nbrInfo.getVar(3) == 3 || nbrInfo.getVar(3) == 8) &&
			tileName == nbrInfo.getName(2) && tileName == nbrInfo.getName(3))
		setTileVariant(11);
	else if((nbrInfo.getVar(0) == 4 || nbrInfo.getVar(0) == 5) && (nbrInfo.getVar(3) == 1 || nbrInfo.getVar(3) == 5) &&
			tileName == nbrInfo.getName(0) && tileName == nbrInfo.getName(3))
		setTileVariant(12);
	
	switch(tileName)
	{
		default:
		case TileName::VOID:
			break;
		case TileName::DIRT:
			break;
		case TileName::GRASS:
			if(nbrInfo.getName(0) == TileName::DIRT && nbrInfo.getName(3) == TileName::DIRT)
				setTileVariant(5);
			else if(nbrInfo.getName(0) == TileName::DIRT && nbrInfo.getName(1) == TileName::DIRT)
				setTileVariant(6);
			else if(nbrInfo.getName(1) == TileName::DIRT && nbrInfo.getName(2) == TileName::DIRT)
				setTileVariant(7);
			else if(nbrInfo.getName(2) == TileName::DIRT && nbrInfo.getName(3) == TileName::DIRT)
				setTileVariant(8);
			else if(nbrInfo.getName(0) == TileName::DIRT)
				setTileVariant(1);
			else if(nbrInfo.getName(1) == TileName::DIRT)
				setTileVariant(2);
			else if(nbrInfo.getName(2) == TileName::DIRT)
				setTileVariant(3);
			else if(nbrInfo.getName(3) == TileName::DIRT)
				setTileVariant(4);
			/*else if(nbrInfo.getName(0) == TileName::GRASS && nbrInfo.getName(1) == TileName::GRASS &&
					(nbrInfo.getVar(0) == 2 || nbrInfo.getVar(0) == 6) && (nbrInfo.getVar(1) == 1 || nbrInfo.getVar(1) == 6))
				setTileVariant(9);
			else if(nbrInfo.getName(1) == TileName::GRASS && nbrInfo.getName(2) == TileName::GRASS &&
					(nbrInfo.getVar(1) == 3 || nbrInfo.getVar(1) == 7) && (nbrInfo.getVar(2) == 2 || nbrInfo.getVar(2) == 7))
				setTileVariant(10);
			else if(nbrInfo.getName(2) == TileName::GRASS && nbrInfo.getName(3) == TileName::GRASS &&
					(nbrInfo.getVar(2) == 4 || nbrInfo.getVar(2) == 8) && (nbrInfo.getVar(3) == 3 || nbrInfo.getVar(3) == 8))
				setTileVariant(11);
			else if(nbrInfo.getName(0) == TileName::GRASS && nbrInfo.getName(3) == TileName::GRASS &&
					(nbrInfo.getVar(0) == 4 || nbrInfo.getVar(0) == 5) && (nbrInfo.getVar(3) == 1 || nbrInfo.getVar(3) == 5))
				setTileVariant(12);*/
			break;
		case TileName::LAKE:
			if(nbrInfo.getName(0) == TileName::GRASS && nbrInfo.getName(3) == TileName::GRASS)
				setTileVariant(5);
			else if(nbrInfo.getName(0) == TileName::GRASS && nbrInfo.getName(1) == TileName::GRASS)
				setTileVariant(6);
			else if(nbrInfo.getName(1) == TileName::GRASS && nbrInfo.getName(2) == TileName::GRASS)
				setTileVariant(7);
			else if(nbrInfo.getName(2) == TileName::GRASS && nbrInfo.getName(3) == TileName::GRASS)
				setTileVariant(8);
			else if(nbrInfo.getName(0) == TileName::GRASS)
				setTileVariant(1);
			else if(nbrInfo.getName(1) == TileName::GRASS)
				setTileVariant(2);
			else if(nbrInfo.getName(2) == TileName::GRASS)
				setTileVariant(3);
			else if(nbrInfo.getName(3) == TileName::GRASS)
				setTileVariant(4);
			/*else if(nbrInfo.getName(0) == TileName::LAKE && nbrInfo.getName(1) == TileName::LAKE &&
					(nbrInfo.getVar(0) == 2 || nbrInfo.getVar(0) == 6) && (nbrInfo.getVar(1) == 1 || nbrInfo.getVar(1) == 6))
				setTileVariant(9);
			else if(nbrInfo.getName(1) == TileName::LAKE && nbrInfo.getName(2) == TileName::LAKE &&
					(nbrInfo.getVar(1) == 3 || nbrInfo.getVar(1) == 7) && (nbrInfo.getVar(2) == 2 || nbrInfo.getVar(2) == 7))
				setTileVariant(10);
			else if(nbrInfo.getName(2) == TileName::LAKE && nbrInfo.getName(3) == TileName::LAKE &&
					(nbrInfo.getVar(2) == 4 || nbrInfo.getVar(2) == 8) && (nbrInfo.getVar(3) == 3 || nbrInfo.getVar(3) == 8))
				setTileVariant(11);
			else if(nbrInfo.getName(0) == TileName::LAKE && nbrInfo.getName(3) == TileName::LAKE &&
					(nbrInfo.getVar(0) == 4 || nbrInfo.getVar(0) == 5) && (nbrInfo.getVar(3) == 1 || nbrInfo.getVar(3) == 5))
				setTileVariant(12);*/
			break;
	}
}

void Tile::setTileVariant(int variant)
{
	tileVariant = variant;
}

int Tile::getTileVariant()
{
	return tileVariant;
}
