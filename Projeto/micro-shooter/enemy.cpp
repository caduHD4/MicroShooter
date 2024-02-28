#include "enemy.hpp"

Enemy::Enemy()
{
	x = 100;
	y = 100;
	width = 40;
	height = 40;
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
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
}