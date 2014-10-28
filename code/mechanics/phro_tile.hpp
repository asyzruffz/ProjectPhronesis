/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#ifndef PHRO_TILE_HPP
#define PHRO_TILE_HPP

#include <string>
using namespace std;

#include <SFML/Graphics.hpp>

enum class TileName { VOID, DIRT, GRASS, LAKE };
enum class TileType { VOID, FLOOR, OBSTACLE, PORTAL };

string tileNameToStr(TileName name);
TileName intTotileName(int name);

class Tile
{
public:
	
	Tile(): tileName(TileName::VOID), tileType(TileType::VOID), tileVariant(0) {}
	Tile(const TileName tileName, const TileType tileType);
	
	void draw(sf::RenderWindow& window);
    void update(float dt);
	
	void setTileVariant(int variant);
	int getTileVariant();
	
	sf::Sprite sprite;
	TileName tileName;
	
private:
	
	/* Tile variant, allowing for different looking versions of the
     * same tile */
    int tileVariant;
	TileType tileType;
};

#endif // PHRO_TILE_HPP
