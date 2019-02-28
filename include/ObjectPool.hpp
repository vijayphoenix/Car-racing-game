/**
 * @file ObjectPool.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2019-02-28
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef OBJECTPOOL_HPP
#define OBJECTPOOL_HPP

#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include <memory>
#include "Car.hpp"
#include "Bot.hpp"
#include "Game.hpp"
#include "Bullet.hpp"

namespace cp
{
template<class T>
class ObjectPool
{
  public:
    ObjectPool(size_t size) : max_pool_size(size)
    {
    }
	// ~ObjectPool();

  T* getObject(GameDataRef _data, int car_num)
  {
    if(!obj_list.empty()){
      T* obj = obj_list.front();
      obj_list.pop_front();
      return obj;
    }
    else if(obj_made < max_pool_size){
      obj_made++;
      std::cout<<obj_made<<std::endl;
      return new T(_data, car_num);
    }
    else std::cerr<<"MAX OBJECTPOOL SIZE LIMIT REACHED"<<std::endl;
  }

  void returnObject(T* obj)
  {
    obj->reset();
    obj_list.push_back(obj);
  }

  private:
    std::list<T*> obj_list;
    size_t max_pool_size;
    size_t obj_made=0;
};
} // namespace cp
#endif //OBJECTPOOL_HPP