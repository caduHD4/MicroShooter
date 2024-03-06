#include "player.hpp"

Player::Player()
{
	// float dt = 20;
	// this->position += this->speed * dt;
	Vector position = Vector(400, 400);
	Vector speed = Vector(6, 1);
	this->setPosition(position);
	this->setSpeed(speed);
	this->setWidth(40.0);
	this->setHeight(40.0);
	this->setLife(3);
}

void Player::draw(SDL_Renderer* renderer)
{
	this->rect.x = this->getPosition().x;
	this->rect.y = this->getPosition().y;
	this->rect.w = this->getWidth();
	this->rect.h = this->getHeight();
	SDL_SetRenderDrawColor(renderer, 32, 33, 36, 255);
	SDL_RenderFillRect(renderer, &rect);
}

void Player::moveUp()
{
	float finalPosition = getPosition().y - (getSpeed().x * getSpeed().y);
	Vector finalVector = Vector(getPosition().x, finalPosition);
	setPosition(finalVector);
}

void Player::moveDown()
{
	float finalPosition = getPosition().y + (getSpeed().x * getSpeed().y);
	Vector finalVector = Vector(getPosition().x, finalPosition);
	setPosition(finalVector);
}

void Player::moveRight()
{
	float finalPosition = getPosition().x + (getSpeed().x * getSpeed().y);
	Vector finalVector = Vector(finalPosition, getPosition().y);
	setPosition(finalVector);
}

void Player::moveLeft()
{
	float finalPosition = getPosition().x - (getSpeed().x * getSpeed().y);
	Vector finalVector = Vector(finalPosition, getPosition().y);
	setPosition(finalVector);
}