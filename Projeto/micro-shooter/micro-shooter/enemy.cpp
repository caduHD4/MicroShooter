#include "enemy.hpp"

Enemy::Enemy()
{
	x = 100;
	y = 100;
	width = 20;
	height = 20;
	vspeed = 6;
	hspeed = 6;
	life = 3;
}

void Enemy::draw(SDL_Renderer* renderer)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;
	SDL_SetRenderDrawColor(renderer, 32, 33, 36, 255);
	SDL_RenderFillRect(renderer, &rect);
}