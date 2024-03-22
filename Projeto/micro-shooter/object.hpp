#ifndef object_hpp
#define object_hpp

#include <stdio.h>
#include <iostream>
#include "math-vector.h"

using Vector = Mylib::Math::Vector<float, 2>;
class Object {
	
protected:
	int life;
	float height;
	float width;
	Vector speed;
	Vector position;

public:
	Vector getSpeed() {
		return this->speed;
	}
	void setSpeed(Vector speed)
	{
		this->speed = speed;
	}
	Vector getPosition() 
	{
		return this->position;
	}
	void setPosition(Vector position)
	{
		this->position = position;
	}
	int getLife() 
	{
		return this->life;
	}
	void setLife(int life)
	{
		this->life = life;
	}
	float getWidth() 
	{
		return this->width;
	}
	void setWidth(float width)
	{
		this->width = width;
	}
	float getHeight() 
	{
		return this->height;
	}
	void setHeight(float height)
	{
		this->height = height;
	}
};
#endif