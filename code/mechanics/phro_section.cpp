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
	for(int y = 1; y < height - 1; y++)
	{
		for(int x = 1; x < width - 1; x++)
		{
			tiles[width*y + x].nbrInfo.set(0, tiles[width*(y-1) + x].tileName, tiles[width*(y-1) + x-1].getTileVariant());
			tiles[width*y + x].nbrInfo.set(1, tiles[width*y + x+1].tileName, tiles[width*(y-1) + x-1].getTileVariant());
			tiles[width*y + x].nbrInfo.set(2, tiles[width*(y+1) + x].tileName, tiles[width*(y-1) + x-1].getTileVariant());
			tiles[width*y + x].nbrInfo.set(3, tiles[width*y + x-1].tileName, tiles[width*(y-1) + x-1].getTileVariant());
			//tiles[width*y + x].nbrInfo.set(4, tiles[width*(y-1) + x-1].tileName, tiles[width*(y-1) + x-1].getTileVariant());
			//tiles[width*y + x].nbrInfo.set(5, tiles[width*(y-1) + x+1].tileName, tiles[width*(y-1) + x-1].getTileVariant());
			//tiles[width*y + x].nbrInfo.set(6, tiles[width*(y+1) + x+1].tileName, tiles[width*(y-1) + x-1].getTileVariant());
			//tiles[width*y + x].nbrInfo.set(7, tiles[width*(y+1) + x-1].tileName, tiles[width*(y-1) + x-1].getTileVariant());
		}
	}
	
	for(int i = 0; i < (width * height); i++)
	{
		tiles[i].update();
		
		char tVar1 = '0' + (tiles[i].getTileVariant() / 10);
		char tVar2 = '0' + (tiles[i].getTileVariant() % 10);
		string tName = tileNameToStr(tiles[i].tileName) + tVar1 + tVar2;
		
		//cout << "Variant: " << tName << endl;
		tiles[i].sprite.setTexture(rsc->getTextureRef(tName));
	}
}

void Section::acquireResource(ResourceManager* source)
{
	rsc = source;
	
	for(int i = 0; i < (width * height); i++)
	{
		tiles[i].sprite.setTexture(rsc->getTextureRef(tileNameToStr(tiles[i].tileName) + "00"));
	}
	
	updateTileVariant();
}
