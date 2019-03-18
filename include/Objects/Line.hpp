#ifndef LINE_HPP
#define LINE_HPP

#include <SFML/Graphics.hpp>
namespace cp{
	class Line{
		public:
		Line	(){}
		~Line	(){}

		float x = 0, y = 0, z = 0; //3d center of line
		float no_curve_Y=0;
		float no_curve_X=0;
		float X = 0, Y = 0, W = 0; //screen coord and width of line on screen
		float curve = 0, spriteX = 0, clip = 0;
		float scale = 0;
		sf::Sprite sprite;
  		private:
	};
}
#endif //LINE_HPP