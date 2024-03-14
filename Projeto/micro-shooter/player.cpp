#include "player.hpp"

Player::Player()
{
	SDL_Rect sdlRect = SDL_Rect();
	setRect(sdlRect);
	// float dt = 20;
	// this->position += this->speed * dt;
	Vector position = Vector(400, 400);
	Vector speed = Vector(300, 300);
	this->setPosition(position);
	this->setSpeed(speed);
	this->setWidth(40.0);
	this->setHeight(40.0);
	this->setLife(3);
}

void Player::draw(SDL_Renderer* renderer)
{
	this->rect.x = getPosition().x;
	this->rect.y = getPosition().y;
	this->rect.w = getWidth();
	this->rect.h = getHeight();
	SDL_SetRenderDrawColor(renderer, 32, 33, 36, 255);
	SDL_RenderFillRect(renderer, &rect);
}

void Player::moveUp(float frameTime)
{
	this->position.y -= getSpeed().y * frameTime;
}

void Player::moveDown(float frameTime)
{
	this->position.y += getSpeed().y * frameTime;
}

void Player::moveRight(float frameTime)
{
	this->position.x += getSpeed().x * frameTime;
}

void Player::moveLeft(float frameTime)
{
	this->position.x -= getSpeed().x * frameTime;
}