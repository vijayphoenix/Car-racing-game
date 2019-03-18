/**
 * @file ObjectPool.hpp
 * @author Vijay
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
#include "Objects/Car.hpp"
#include "Objects/Bot.hpp"
#include "Game.hpp"
#include "Objects/Bullet.hpp"

namespace cp
{
template<class T>
class ObjectPool
{
  public:
    ObjectPool(size_t size) : max_pool_size(size) {
    }
	~ObjectPool(){
    obj_list.clear();
  }

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
  size_t obj_made=0;
  const size_t max_pool_size;

  private:
    std::list<T*> obj_list;
};
} // namespace cp
#endif //OBJECTPOOL_HPP