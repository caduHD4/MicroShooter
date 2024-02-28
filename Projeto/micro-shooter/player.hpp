#define player_hpp
#include <stdio.h>
#include <iostream>
#include "SDL.h"
#include "object.hpp"

class Player : public Object {
public:
	Player();
	void draw(SDL_Renderer* renderer);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

private:
	SDL_Renderer *renderer;
};