#define enemy_hpp
#include <stdio.h>
#include <iostream>
#include "SDL.h"
#include "object.hpp"

class Enemy : public Object {
public:
	Enemy();
	void draw(SDL_Renderer* renderer);

};