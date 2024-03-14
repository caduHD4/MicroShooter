#define bullet_hpp
#include <stdio.h>
#include <iostream>
#include "SDL.h"
#include "object.hpp"

class Bullet : public Object {
private:
	SDL_Rect rect;

public:
	Bullet();
	Bullet(Vector position);
	void draw(SDL_Renderer* renderer);
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