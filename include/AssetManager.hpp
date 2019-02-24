#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include <map>
#include <SFML/Graphics.hpp>

namespace cp
{
	class AssetManager
	{
	private:
		std::map<std::string, sf::Texture> 	map_texture;
		std::map<std::string, sf::Font> 	map_font;

	public:
		AssetManager					();
		~AssetManager					();

		void 		load_texture		(std::string name, std::string file_name);
		void 		load_font			(std::string name, std::string file_name);
		sf::Texture&get_texture			(std::string name);
		sf::Font&	get_font			(std::string name);
	};
}
#endif //ASSETMANAGER_HPP