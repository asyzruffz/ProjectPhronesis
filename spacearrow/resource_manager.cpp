/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#include "resource_manager.hpp"

void ResourceManager::loadTexture(const string& name, const string &filename)
{
	sf::Texture tex;
    if(!tex.loadFromFile(filename))
    {
        cout << "ResourceManager: Fail loading [" << filename << "]" << endl;
        exit(1);
    }

    textures[name] = tex;
}

void ResourceManager::loadFont(const string& name, const string &filename)
{
	sf::Font fon;
    if(!fon.loadFromFile(filename))
    {
        cout << "ResourceManager: Fail loading [" << filename << "]" << endl;
        exit(1);
    }

    fonts[name] = fon;
}

void ResourceManager::loadSfx(const string& name, const string &filename)
{
	sf::SoundBuffer soun;
    if(!soun.loadFromFile(filename))
    {
        cout << "ResourceManager: Fail loading [" << filename << "]" << endl;
        exit(1);
    }

    sfx[name] = soun;
}

sf::Texture& ResourceManager::getTextureRef(const string& texture)
{
	if(textures.count(texture) != 1)
		cout << "ResourceManager: Cannot find texture [" << texture << "]" << endl;
	else
		return textures.at(texture);
}

sf::Font* ResourceManager::getFontRef(const string& font)
{
	if(fonts.count(font) != 1)
		cout << "ResourceManager: Cannot find font [" << font << "]" << endl;
	else
		return &fonts.at(font);
}

sf::SoundBuffer& ResourceManager::getSfxRef(const string& sound)
{
	if(sfx.count(sound) != 1)
		cout << "ResourceManager: Cannot find sound [" << sound << "]" << endl;
	else
		return sfx.at(sound);
}
