#include "player.hpp"

Player::Player()
{
	x = 400;
	y = 400;
	width = 40;
	height = 40;
	vspeed = 6;
	hspeed = 6;
	life = 3;
}

void Player::draw(SDL_Renderer* renderer)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;
	SDL_SetRenderDrawColor(renderer, 32, 33, 36, 255);
	SDL_RenderFillRect(renderer, &rect);
}

void Player::moveUp()
{
	y -= vspeed;
}

void Player::moveDown()
{
	y += vspeed;
}

void Player::moveRight()
{
	x += hspeed;

}

void Player::moveLeft()
{
	x -= hspeed;
}