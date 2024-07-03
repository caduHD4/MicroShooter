#define bullet_hpp
#include <stdio.h>
#include <iostream>
#include "SDL.h"
#include "object.hpp"

class Bullet : public Object {

public:
	Bullet();
	Bullet(Vector position);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

};