#include "GameMap.hpp"

namespace cp{
	GameMap::GameMap(GameDataRef _data) : data(_data){
	}
	void GameMap::init() {

		// TODO : Create a helper function to load all the assets required for GameMap
		/////////// Loading Environment assets ////////
		for (int i = 1; i <= 9; i++)
		{
			t[i].loadFromFile("res/" + std::to_string(i) + ".png");
			t[i].setSmooth(true);
			object[i].setTexture(t[i]);
		}
		data->assets.load_texture("GameStateBackground", GAME_STATE_BACKGROUND_FILEPATH);
		data->assets.get_texture("GameStateBackground").setRepeated(true);
		background_sprite.setTexture(data->assets.get_texture("GameStateBackground"));
		background_sprite.setTextureRect(sf::IntRect(0, 0, 6000, 411));
		background_sprite.setPosition(-2000, 0);
		///////////////////////////////////////////////


		// TODO : Create a map generator function
		//////// Geerating map //////////////////////
		for (int i = 0; i < 1600; i++)
		{
			Line line;
			line.z = i * segL;
			if (i > 300 && i < 700)
				line.curve = 0.5;
			if (i > 1100)
				line.curve = -0.7;

			if (i < 300 && i % 20 == 0)
			{
				line.spriteX = -2.5;
				line.sprite = object[5];
			}
			if (i % 17 == 0)
			{
				line.spriteX = 2.0;
				line.sprite = object[6];
			}
			if (i > 300 && i % 20 == 0)
			{
				line.spriteX = -0.7;
				line.sprite = object[4];
			}
			if (i > 800 && i % 20 == 0)
			{
				line.spriteX = -1.2;
				line.sprite = object[1];
			}
			if (i == 400)
			{
				line.spriteX = -1.2;
				line.sprite = object[7];
			}
			if (i > 750)
				line.y = sin(i / 30.0) * 1500;
			lines.push_back(line);
		}
		N = lines.size();
		////////////////////////////////////////////
	}
	void GameMap::draw_quad(sf::Color c, int x1, int y1, int w1, int x2, int y2, int w2) {
		sf::ConvexShape shape(4);
		shape.setFillColor(c);
		shape.setPoint(0, sf::Vector2f(x1 - w1, y1));
		shape.setPoint(1, sf::Vector2f(x2 - w2, y2));
		shape.setPoint(2, sf::Vector2f(x2 + w2, y2));
		shape.setPoint(3, sf::Vector2f(x1 + w1, y1));
		data->window.draw(shape);
	}
	void GameMap::project(Line &line, int camX, int camY, int camZ, float camD) {
		line.scale = camD / (line.z - camZ);

		// If line.scale > 1 (threshold ) then the line is between the camera and the projection plane
		// So it is not visible on the screen and hence no need to over scale it.
		if(line.scale>1.1 || line.scale<0)line.scale = 1.1;
		////////////////////////////////////////////////////////////////////////////////////

		line.X = (1 + line.scale * (line.x - camX)) * width / 2;
		line.Y = (1 - line.scale * (line.y - camY)) * height / 2;
		line.W = line.scale * roadW * width /2;

		// // Debug codes
		// static int x = 1;x++;
		// if(x>5) {/*  exit(1); */ }
		// else {
		// 	std::cout<<std::endl;
		// 	std::cout<<"{ Scale: "<<line.scale<<std::endl;
		// 	std::cout<<"{ Position-> Z: "<<line.z<<" Y: "<<line.y<<" X: "<<line.x<<std::endl;
		// 	std::cout<<"{ Camera  -> Z: "<<camZ<<" Y: "<<camY<<" X: "<<camX<<std::endl;
		// 	std::cout<<"{ Width: "<<line.W<<" X: "<<line.X<<" Y: "<<line.Y<<std::endl;

		// }
	}
	void GameMap::drawSprite(Line &line) {
		sf::Sprite s = line.sprite;
		int w = s.getTextureRect().width;
		int h = s.getTextureRect().height;

		float destX = line.X + line.scale * line.spriteX * width / 2;
		float destY = line.Y + 4	;
		float destW = w * line.W / 266;
		float destH = h * line.W / 266;

		destX += destW * line.spriteX; //offsetX
		destY += destH * (-1);		   //offsetY

		float clipH = destY + destH - line.clip;
		// Debug codes
		static int x = 1;x++;
		if(x>5) {/*  exit(1); */ }
		else {
			std::cout<<std::endl;
			std::cout<<"{ Scale: "<<line.scale<<std::endl;
			std::cout<<"{ Position-> Z: "<<line.z<<" Y: "<<line.y<<" X: "<<line.x<<std::endl;
			std::cout<<"{ Width: "<<line.W<<" X: "<<line.X<<" Y: "<<line.Y<<std::endl;
			std::cout<<"{ Clip: "<<line.clip<<std::endl;

		}
		if (clipH < 0)clipH = 0;
		if (clipH >= destH)	return;
		s.setTextureRect(sf::IntRect(0, 0, w, h - h * clipH / destH));
		s.setScale(destW / w, destH / h);
		s.setPosition(destX, destY);
		data->window.draw(s);
	}
	void GameMap::draw(int count, std::unique_ptr<PlayerCar> &car, Camera& main_camera) {
		data->window.draw(background_sprite);

		// TODO : Implement functions for camera
		////// Finding camera position and camera height ///
		int startPos = car->pos / segL;
		int camH = lines[startPos].y + main_camera.H; // Don't update camera height
		///////////////////////////////////////////////////

		int maxy=height;
		float x=0,dx=0;

		for (int n = startPos; n < startPos + count; n++)
		{
			Line &l = lines[n % N];
			///// Changing the view at each drawing of line to give effect of curves and height.
			project(l, car->playerX * roadW - x, camH, startPos * segL - (n >= N ? N * segL : 0), main_camera.camD);
			x += dx;
			dx += l.curve;

			// static int times = 0;
			// if(times<10000000) { std::cout<<x<<std::endl;times++; }
			// std::cout<<playerX<<std::endl;

			l.clip = maxy;
			if (l.Y >= maxy)continue;
			maxy = l.Y;

			sf::Color grass = (n / 3) % 2 ? sf::Color(16, 200, 16) : sf::Color(0, 154, 0);
			sf::Color marking = (n / 3) % 2 ? sf::Color::White : sf::Color(105, 105, 105);
			sf::Color rumble = (n / 3) % 2 ? sf::Color(255, 255, 255) : sf::Color(0, 0, 0);
			sf::Color road = (n / 3) % 2 ? sf::Color(107, 107, 107) : sf::Color(105, 105, 105);

			Line p = lines[(n - 1) % N];

			draw_quad(grass, 0, p.Y, width, 0, l.Y, width);
			draw_quad(rumble, p.X, p.Y, p.W *1.1, l.X, l.Y, l.W * 1.1);
			draw_quad(road, p.X, p.Y, p.W, l.X, l.Y, l.W);

			draw_quad(marking,(p.X),p.Y,p.W*0.35,l.X,l.Y,l.W*0.35);
			draw_quad(road, p.X, p.Y, p.W*0.3, l.X, l.Y, l.W*0.3);

		}
	}

}