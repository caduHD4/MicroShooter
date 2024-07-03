#ifndef player_hpp
#define player_hpp

#include <iostream>
#include "object.hpp"

struct Rect {
	Vector position;
	float width;
	float height;
};

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

	Rect getRect() {
		return this->rect;
	}

	void setRect(Rect rect) {
		this->rect = rect;
	}
};
#endif