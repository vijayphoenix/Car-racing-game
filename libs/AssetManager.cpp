#include "AssetManager.hpp"
#include <iostream>

namespace cp{
void AssetManager::load_texture(std::string name, std::string file_name)
{
	sf::Texture texture;
	if (texture.loadFromFile(file_name))
		map_texture[name] = texture;
	else
		std::cout << "FAILED TO LOAD TEXTURE";
}

sf::Texture& AssetManager::get_texture(std::string name)
{
	return map_texture.at(name);
}

void AssetManager::load_font(std::string name, std::string file_name)
{
	sf::Font font;
	if (font.loadFromFile(file_name))
		map_font[name] = font;
	else
		std::cout << "FAILED TO LOAD FONT";
}

sf::Font& AssetManager::get_font(std::string name)
{
	return map_font.at(name);
}
}