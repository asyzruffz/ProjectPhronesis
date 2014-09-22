/***** P R O J E C T   P H R O N E S I S *****
*********************************************/

#include "phro_resource_manager.hpp"

void ResourceManager::loadTexture(const string& name, const string &filename)
{
	sf::Texture tex;
    if(!tex.loadFromFile(filename))
    {
        cout << "Fail loading [" << filename << "]" << endl;
        exit(1);
    }

    textures[name] = tex;
}

void ResourceManager::loadFont(const string& name, const string &filename)
{
	sf::Font fon;
    if(!fon.loadFromFile(filename))
    {
        cout << "Fail loading [" << filename << "]" << endl;
        exit(1);
    }

    fonts[name] = fon;
}

void ResourceManager::loadSfx(const string& name, const string &filename)
{
	sf::SoundBuffer soun;
    if(!soun.loadFromFile(filename))
    {
        cout << "Assets Manager: Fail loading [" << filename << "]" << endl;
        exit(1);
    }

    sfx[name] = soun;
}

sf::Texture& ResourceManager::getTextureRef(const string& texture)
{
	return textures.at(texture);
}

sf::Font* ResourceManager::getFontRef(const string& font)
{
	return &fonts.at(font);
}

sf::SoundBuffer& ResourceManager::getSfxRef(const string& sound)
{
	return sfx.at(sound);
}
