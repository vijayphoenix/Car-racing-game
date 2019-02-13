#include <iostream>
#include <cmath>
#include <sstream>
#include "GameState.hpp"
#include "DEFINITIONS.hpp"

namespace cp
{
	GameState::GameState(GameDataRef _data) : data(_data), map(_data){
	}
	void GameState::init() {

		// TODO : Create a helper function to load all the assets required for gamestate
		map.init();

		////////// Loading Car assets ////////////////
		for(int i = 0; i < TOTAL_CARS; i++)
		{
			data->assets.load_texture("CarImage"+std::to_string(i),CAR_IMAGE_FILEPATH(i));
		}
		//////////////////////////////////////////////

		// TODO : Create an object pool
		/////// Creating the main player car and bots
		car = std::unique_ptr<PlayerCar>(new PlayerCar(data,5,main_camera.speed));
		for(int i=0;i<TOTAL_BOTS;i++){
			bot[i] = std::unique_ptr<Bot>(new Bot(data, 5));
			bot_pos[i]=i*10;
		}
		///////////////////////////////////////////////

		////// The Game Begins ///////////////////////
		current_time=clock.getElapsedTime().asSeconds();
		//////////////////////////////////////////////
	}
	void GameState::handle_input() {
		sf::Event event;
		while(data->window.pollEvent(event))
			if(sf::Event::Closed==event.type){
				data->window.close();
			}

		//////////// Debug Sections ///////////
		handle_road_width(5); // W+ S-
		handle_segL(5); // O+ L-
		handle_camD(0.01); //I+ K-
		////////////////////////////////////////

		new_time=clock.getElapsedTime().asSeconds();

		// TODO : Create a driver/bot_mind class
		/////// The driver handles the players car ////////
		car->update_car(new_time - current_time, map.lines, map.segL);
		//////////////////////////////////////////////////

		// TODO : Implement the camera class
		////// Updating the players position pos ///////////////////////
		car->pos += main_camera.speed;
		while (car->pos >= map.N * map.segL)
			car->pos -= map.N * map.segL;
		while (car->pos < 0)
			car->pos += map.N * map.segL;
		//////////////////////////////////////////////////

		////// The frame Ends ///////////////////////////
		current_time = new_time;
		////////////////////////////////////////////////
	}
	void GameState::draw(float delta){
		data->window.clear(sf::Color(105, 205, 4));

		// TODO : Implement functions for camera
		////// Finding camera position and camera height ///
		int startPos = car->pos / map.segL;
		int camH = map.lines[startPos].y + main_camera.H; // Don't update camera height
		///////////////////////////////////////////////////
		map.draw(500, car, main_camera);

		for (int i = 0; i < TOTAL_BOTS; i++)
			bot[i]->drawSprite(map.lines[bot_pos[i]]);
		for (int n = startPos + 500; n >startPos; n--) {
			drawSprite(map.lines[n % map.N]);
			for (int i = 0; i < TOTAL_BOTS; i++)
				if (bot_pos[i] >= n - 1 and bot_pos[i] <= n + 1)
					bot[i]->drawSprite(map.lines[bot_pos[i]]);
		}
		for (int i = 0; i < TOTAL_BOTS; i++) {
			temp++;
			if(temp%(2*i+1)==0)bot_pos[i]+=(i+1);
			temp%=map.N;
			bot_pos[i] %= map.N;
			int diff = bot_pos[i] % map.N - (car->pos / map.segL) % map.N;

			if (std::abs(diff) <= 8)
			{
				if (diff > 7 and collision.detect_collision(car->sprite, bot[i]->sprite))
				{
					main_camera.speed = 0;
				}
				else if (diff <= 7 and collision.detect_collision(bot[i]->sprite, car->sprite))
				{
					main_camera.speed += 100;
				}
			}
		}

		car->draw_car();
		data->window.display();
	}
	void GameState::update(float delta){
	}
	void GameState::drawSprite(Line &line) {
		s = line.sprite;
		int w = s.getTextureRect().width;
		int h = s.getTextureRect().height;

		float destX = line.X + line.scale * line.spriteX * map.width / 2;
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
}
