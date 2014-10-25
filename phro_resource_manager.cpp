/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

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
	if(textures.count(texture) != 1)
		cout << "Assets Manager: Cannot find texture [" << texture << "]" << endl;
	else
		return textures.at(texture);
}

sf::Font* ResourceManager::getFontRef(const string& font)
{
	if(fonts.count(font) != 1)
		cout << "Assets Manager: Cannot find font [" << font << "]" << endl;
	else
		return &fonts.at(font);
}

sf::SoundBuffer& ResourceManager::getSfxRef(const string& sound)
{
	if(sfx.count(sound) != 1)
		cout << "Assets Manager: Cannot find sound [" << sound << "]" << endl;
	else
		return sfx.at(sound);
}
