#ifndef player_hpp
#define player_hpp

#include <iostream>
#include "object.hpp"

class Player : public Object
{
	public:
		Player();
		void moveUp(float frameTime);
		void moveDown(float frameTime);
		void moveLeft(float frameTime);
		void moveRight(float frameTime);
};
#endif