/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#ifndef PHRO_RESOURCE_MANAGER_HPP
#define PHRO_RESOURCE_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <map>
using namespace std;

class ResourceManager
{
public:
	
	ResourceManager(){}
	
	//Add from a file
	void loadTexture(const string& name, const string &filename);
    void loadFont(const string& name, const string &filename);
    void loadSfx(const string& name, const string &filename);
	
	//Translate an id into a reference or pointer
    sf::Texture& getTextureRef(const string& texture);
	sf::Font* getFontRef(const string& font);
	sf::SoundBuffer& getSfxRef(const string& sound);
	
private:
	
	//Resources stored here
	map<string, sf::Texture> textures;
    map<string, sf::Font> fonts;
    map<string, sf::SoundBuffer> sfx;
};

#endif // PHRO_RESOURCE_MANAGER_HPP
