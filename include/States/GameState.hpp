#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <set>
#include <vector>
#include "States/GameOverState.hpp"
#include "DEFINITIONS.hpp"
#include "Objects/Bot.hpp"
#include "Objects/PlayerCar.hpp"
#include "States/State.hpp"
#include "Game.hpp"
#include "Objects/Line.hpp"
#include "Physics/Collision.hpp"
#include "Objects/Camera.hpp"
#include "Objects/GameMap.hpp"
#include "States/PauseState.hpp"
#include "PercentageBar.hpp"
#include "Objects/Bullet.hpp"
#include "ObjectPool.hpp"

namespace cp
{
    class GameState : public State {
        public:

        GameState               (GameDataRef _data);
        ~GameState              () {}
        virtual void init		            ();
        virtual void handle_input       (float delta);


        private:

        using CarRef = std::shared_ptr<PlayerCar>;
        using BotRef = std::shared_ptr<Bot>;
        GameDataRef data;
        GameMap map;
        Camera main_camera;
        CarRef car;
        CarRef    bot[TOTAL_BOTS];
        Collision               collision;
        /////////////////////////////////

        PercentageBar bar;
        sf::Font font;
        sf::Text text[5];
        double score=0;
        // float fuel =100;
        ObjectPool<Bullet>pool;
        Bullet* bullet;
        std::set<Bullet*> bullet_set[2];
        int current=0;

        virtual void draw(float delta) {
            data->window.clear(sf::Color(105, 205, 4));
            map.draw(500, main_camera);
            for (int i = 0; i < TOTAL_BOTS; i++)
            {
                //////////// Temp Update ///////////
                int index = map.get_grid_index(bot[i]->e_position.z);
                Line &temp_line = map.lines[index];
                bot[i]->drawSprite(map.lines[index]);
            }
            //// Finding camera position and camera height ///
            int startPos = map.get_grid_index(main_camera.getPosition().z);
            /////////////////////////////////////////////////
            for (int n = startPos + 500; n > startPos; n--)
            {
                drawSprite(map.lines[n % map.getGridCount()]);
                for (int i = 0; i < TOTAL_BOTS; i++)
                {
                    int index = (bot[i]->e_position.z) / map.getSegL();
                    if (index >= n - 1 and index <= n + 1)
                    {
                        bot[i]->drawSprite(map.lines[index]);
                    }
                }
            }
            for (auto itr : bullet_set[current])
            {
                int index = (itr->e_position.z) / map.getSegL();
                itr->drawSprite(map.lines[index]);
            }

            int index = map.get_grid_index(car->e_position.z);
            Line &temp_line = map.lines[index];
            car->drawSprite(map.lines[index]);
            bar.draw();

            for (int i = 0; i < 3; i++)
            {
                data->window.draw(text[i]);
            }
            data->window.display();
            // if (bot[0]->health == 0)bot[0] = std::unique_ptr<Bot>(new Bot(data, 5));
        }

        void update(float delta) {
            if (car->e_speed.z > 0)
                score += delta * car->e_speed.z;
            for (auto itr : bullet_set[current])
                itr->update_car(delta, map.lines, map.getSegL());
            car->update_car(delta, map.lines, map.getSegL());
            for (int i = 0; i < TOTAL_BOTS; i++)
            {
                bot[i]->update_car(delta, map.lines, map.getSegL());

                // int index = map.get_grid_index(bot[i]->e_position.z);
                // int diff = index % map.getGridCount() - map.get_grid_index(car->e_position.z) % map.getGridCount();
                collision.handle_collision(*car, *bot[i], map, COEFFICIENT_OF_RESTITUTION);
                for (int j = i + 1; j < TOTAL_BOTS; j++)
                {
                    collision.handle_collision(*bot[j], *bot[i], map, COEFFICIENT_OF_RESTITUTION);
                }
                // if(bot[i]->health==0)score+=1000;
            }

            for (auto itr : bullet_set[current])
            {
                if (itr->e_position.z - car->e_position.z > 10000)
                    itr->in_use = false;
                collision.handle_collision(*itr, *bot[0], map, COEFFICIENT_OF_RESTITUTION);
                if (itr->in_use)
                    bullet_set[!current].insert(itr);
                else
                    pool.returnObject(itr);
            }
            bullet_set[current].clear();
            current = !current;

            bar.percentage = car->health;
            // std::cout << "CAR health" << car->health << std::endl;
            // std::cout << "Bot health" << bot[0]->health << std::endl;
            text[1].setString(std::to_string(score));
            // data->Nmanager.sendData(car->e_position);
            // data->Nmanager.sendData(bot[0]->e_position);
        }
        void drawSprite(Line &line) {
            sf::Sprite s = line.sprite;
            int w = s.getTextureRect().width;
            int h = s.getTextureRect().height;

            float destX = line.X + line.scale * line.spriteX * map.getScreenWidth() / 2;
            float destY = line.Y + 4;
            float destW = w * line.W / 266;
            float destH = h * line.W / 266;

            destX += destW * line.spriteX; //offsetX
            destY += destH * (-1);         //offsetY

            float clipH = destY + destH - line.clip;
            if (clipH < 0)
                clipH = 0;
            if (clipH >= destH)
                return;
            s.setTextureRect(sf::IntRect(0, 0, w, h - h * clipH / destH));
            s.setScale(destW / w, destH / h);
            s.setPosition(destX, destY);
            data->window.draw(s);
        }

}; // namespace cp
}

#endif //GAMESTATE_HPP