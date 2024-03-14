#ifndef enemy_hpp
#define enemy_hpp

#include <iostream>
#include "SDL.h"
#include "object.hpp"

class Enemy : public Object
{
	private:
		SDL_Rect rect;

	public:
		Enemy();
		void draw(SDL_Renderer* renderer);
		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();

		SDL_Rect getRect()
		{
			return this->rect;
		}

		void setRect(SDL_Rect rect)
		{
			this->rect = rect;
		}
};
#endif