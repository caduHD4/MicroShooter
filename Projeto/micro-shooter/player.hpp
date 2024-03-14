#ifndef player_hpp
#define player_hpp

#include <iostream>
#include "SDL.h"
#include "object.hpp"

class Player : public Object
{
	private:
		SDL_Rect rect;

	public:
		Player();
		void draw(SDL_Renderer* renderer) override;
		void moveUp(float frameTime);
		void moveDown(float frameTime);
		void moveLeft(float frameTime);
		void moveRight(float frameTime);

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