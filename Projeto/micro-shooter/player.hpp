#ifndef player_hpp
#define player_hpp

#include <iostream>
#include "object.hpp"
#include "graphic-implement-sdl.hpp"

class Player : public Object
{
private:
	Rect rect;

public:
	Player();
	void moveUp(float frameTime);
	void moveDown(float frameTime);
	void moveLeft(float frameTime);
	void moveRight(float frameTime);

	Rect& getRect() {
		return this->rect;
	}

	void setRect(const Rect& rect) {
		this->rect = rect;
	}
};
#endif