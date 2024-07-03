#ifndef enemy_hpp
#define enemy_hpp

#include <iostream>
#include "object.hpp"

class Enemy : public Object
{
	public:
		Enemy();
		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
};
#endif