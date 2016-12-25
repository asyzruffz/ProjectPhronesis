/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

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

#endif // RESOURCE_MANAGER_HPP
