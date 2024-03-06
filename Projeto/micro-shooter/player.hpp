#define player_hpp
#include <stdio.h>
#include <iostream>
#include "SDL.h"
#include "object.hpp"

class Player : public Object {
private:
	SDL_Rect rect;

public:
	Player();
	void draw(SDL_Renderer* renderer) override final;
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	SDL_Rect* getRect()
	{
		return &this->rect;
	}

	void setRect(SDL_Rect rect)
	{
		this->rect = rect;
	}
};