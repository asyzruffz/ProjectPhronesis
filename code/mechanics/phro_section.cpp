/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#include <fstream>

#include "phro_section.hpp"

Section::Section(int mwidth, int mheight, const string& fileName) : width(mwidth), height(mheight)
{
	ifstream sectionFile;
	sectionFile.open(fileName);
	if(sectionFile.is_open())
	{
		for(int i = 0; i < (width * height); i++)
		{
			int intName;
			sectionFile >> intName;
			tiles.push_back(Tile(intTotileName(intName), TileType::FLOOR));
		}
		
		sectionFile.close();
	}
	else
	{
		cout << "Fail loading [" << fileName << "]" << endl;
		exit(1);
	}
	
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			tiles[width*y + x].sprite.setOrigin(32, 32);
			tiles[width*y + x].sprite.setPosition(sf::Vector2f(x * 64, y * 64) + sf::Vector2f(112,76));
		}
	}
}

void Section::draw(sf::RenderWindow& window)
{
	for(int i = 0; i < (width * height); i++)
		window.draw(tiles[i].sprite);
}

void Section::updateTileVariant()
{
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			switch(tiles[width*y + x].tileName)
			{
				default:
				case TileName::VOID:
					break;
				case TileName::DIRT:
					break;
				case TileName::GRASS:
					if(tiles[width*(y-1) + x].tileName == TileName::DIRT &&
							tiles[width*(y) + x-1].tileName == TileName::DIRT)
						tiles[width*y + x].setTileVariant(5);
					else if(tiles[width*(y-1) + x].tileName == TileName::DIRT &&
							tiles[width*(y) + x+1].tileName == TileName::DIRT)
						tiles[width*y + x].setTileVariant(6);
					else if(tiles[width*(y) + x+1].tileName == TileName::DIRT &&
							tiles[width*(y+1) + x].tileName == TileName::DIRT)
						tiles[width*y + x].setTileVariant(7);
					else if(tiles[width*(y+1) + x].tileName == TileName::DIRT &&
							tiles[width*(y) + x-1].tileName == TileName::DIRT)
						tiles[width*y + x].setTileVariant(8);
					else if(tiles[width*(y-1) + x].tileName == TileName::DIRT)
						tiles[width*y + x].setTileVariant(1);
					else if(tiles[width*(y) + x+1].tileName == TileName::DIRT)
						tiles[width*y + x].setTileVariant(2);
					else if(tiles[width*(y+1) + x].tileName == TileName::DIRT)
						tiles[width*y + x].setTileVariant(3);
					else if(tiles[width*(y) + x-1].tileName == TileName::DIRT)
						tiles[width*y + x].setTileVariant(4);
					else if(tiles[width*(y-1) + x].tileName == TileName::GRASS && tiles[width*(y) + x+1].tileName == TileName::GRASS &&
							(tiles[width*(y-1) + x].getTileVariant() == 2 || tiles[width*(y-1) + x].getTileVariant() == 6) &&
							(tiles[width*(y) + x+1].getTileVariant() == 1 || tiles[width*(y) + x+1].getTileVariant() == 6))
						tiles[width*y + x].setTileVariant(9);
					else if(tiles[width*(y) + x+1].tileName == TileName::GRASS && tiles[width*(y+1) + x].tileName == TileName::GRASS &&
							(tiles[width*(y) + x+1].getTileVariant() == 3 || tiles[width*(y) + x+1].getTileVariant() == 7) &&
							(tiles[width*(y+1) + x].getTileVariant() == 2 || tiles[width*(y+1) + x].getTileVariant() == 7))
						tiles[width*y + x].setTileVariant(10);
					else if(tiles[width*(y+1) + x].tileName == TileName::GRASS && tiles[width*(y) + x-1].tileName == TileName::GRASS &&
							(tiles[width*(y+1) + x].getTileVariant() == 4 || tiles[width*(y+1) + x].getTileVariant() == 8) &&
							(tiles[width*(y) + x-1].getTileVariant() == 3 || tiles[width*(y) + x-1].getTileVariant() == 8))
						tiles[width*y + x].setTileVariant(11);
					else if(tiles[width*(y-1) + x].tileName == TileName::GRASS && tiles[width*(y) + x-1].tileName == TileName::GRASS &&
							(tiles[width*(y-1) + x].getTileVariant() == 4 || tiles[width*(y-1) + x].getTileVariant() == 5) &&
							(tiles[width*(y) + x-1].getTileVariant() == 1 || tiles[width*(y) + x-1].getTileVariant() == 5))
						tiles[width*y + x].setTileVariant(12);
					break;
				case TileName::LAKE:
					if(tiles[width*(y-1) + x].tileName == TileName::GRASS &&
							tiles[width*(y) + x-1].tileName == TileName::GRASS)
						tiles[width*y + x].setTileVariant(5);
					else if(tiles[width*(y-1) + x].tileName == TileName::GRASS &&
							tiles[width*(y) + x+1].tileName == TileName::GRASS)
						tiles[width*y + x].setTileVariant(6);
					else if(tiles[width*(y) + x+1].tileName == TileName::GRASS &&
							tiles[width*(y+1) + x].tileName == TileName::GRASS)
						tiles[width*y + x].setTileVariant(7);
					else if(tiles[width*(y+1) + x].tileName == TileName::GRASS &&
							tiles[width*(y) + x-1].tileName == TileName::GRASS)
						tiles[width*y + x].setTileVariant(8);
					else if(tiles[width*(y-1) + x].tileName == TileName::GRASS)
						tiles[width*y + x].setTileVariant(1);
					else if(tiles[width*(y) + x+1].tileName == TileName::GRASS)
						tiles[width*y + x].setTileVariant(2);
					else if(tiles[width*(y+1) + x].tileName == TileName::GRASS)
						tiles[width*y + x].setTileVariant(3);
					else if(tiles[width*(y) + x-1].tileName == TileName::GRASS)
						tiles[width*y + x].setTileVariant(4);
					else if(tiles[width*(y-1) + x].tileName == TileName::LAKE && tiles[width*(y) + x+1].tileName == TileName::LAKE &&
							(tiles[width*(y-1) + x].getTileVariant() == 2 || tiles[width*(y-1) + x].getTileVariant() == 6) &&
							(tiles[width*(y) + x+1].getTileVariant() == 1 || tiles[width*(y-1) + x].getTileVariant() == 6))
						tiles[width*y + x].setTileVariant(9);
					else if(tiles[width*(y) + x+1].tileName == TileName::LAKE && tiles[width*(y+1) + x].tileName == TileName::LAKE &&
							(tiles[width*(y) + x+1].getTileVariant() == 3 || tiles[width*(y-1) + x].getTileVariant() == 7) &&
							(tiles[width*(y+1) + x].getTileVariant() == 2 || tiles[width*(y-1) + x].getTileVariant() == 7))
						tiles[width*y + x].setTileVariant(10);
					else if(tiles[width*(y+1) + x].tileName == TileName::LAKE && tiles[width*(y) + x-1].tileName == TileName::LAKE &&
							(tiles[width*(y+1) + x].getTileVariant() == 4 || tiles[width*(y-1) + x].getTileVariant() == 8) &&
							(tiles[width*(y) + x-1].getTileVariant() == 3 || tiles[width*(y-1) + x].getTileVariant() == 8))
						tiles[width*y + x].setTileVariant(11);
					else if(tiles[width*(y-1) + x].tileName == TileName::LAKE && tiles[width*(y) + x-1].tileName == TileName::LAKE &&
							(tiles[width*(y-1) + x].getTileVariant() == 4 || tiles[width*(y-1) + x].getTileVariant() == 5) &&
							(tiles[width*(y) + x-1].getTileVariant() == 1 || tiles[width*(y-1) + x].getTileVariant() == 5))
						tiles[width*y + x].setTileVariant(12);
					break;
			}
		}
	}
	
	for(int i = 0; i < (width * height); i++)
		if(tiles[i].getTileVariant() != 0)
		{
			char tVar1 = '0' + (tiles[i].getTileVariant() / 10);
			char tVar2 = '0' + (tiles[i].getTileVariant() % 10);
			string tName = tileNameToStr(tiles[i].tileName) + tVar1 + tVar2;
			
			cout << "Variant: " << tName << endl;
			tiles[i].sprite.setTexture(rsc->getTextureRef(tName));
		}
	return;
}

void Section::acquireResource(ResourceManager* source)
{
	rsc = source;
	
	for(int i = 0; i < (width * height); i++)
	{
		tiles[i].sprite.setTexture(rsc->getTextureRef(tileNameToStr(tiles[i].tileName)));
	}
	
	updateTileVariant();
}
