#include "enemy.hpp"

Enemy::Enemy()
{
	Vector position = Vector(100, 100);
	Vector speed = Vector(6, 1);
	this->setPosition(position);
	this->setSpeed(speed);
	this->setWidth(40);
	this->setHeight(40);
	this->setLife(3);
}

void Enemy::draw(SDL_Renderer* renderer)
{
	this->rect.x = this->getPosition().x;
	this->rect.y = this->getPosition().y;
	this->rect.w = this->getWidth();
	this->rect.h = this->getHeight();
	SDL_SetRenderDrawColor(renderer, 32, 33, 36, 255);
	SDL_RenderFillRect(renderer, &rect);
}

void Enemy::moveUp()
{
	float finalPosition = getPosition().y - (getSpeed().x * getSpeed().y);
	Vector finalVector = Vector(getPosition().x, finalPosition);
	setPosition(finalVector);
}

void Enemy::moveDown()
{
	float finalPosition = getPosition().y + (getSpeed().x * getSpeed().y);
	Vector finalVector = Vector(getPosition().x, finalPosition);
	setPosition(finalVector);
}

void Enemy::moveRight()
{
	float finalPosition = getPosition().x + (getSpeed().x * getSpeed().y);
	Vector finalVector = Vector(finalPosition, getPosition().y);
	setPosition(finalVector);
}

void Enemy::moveLeft()
{
	float finalPosition = getPosition().x - (getSpeed().x * getSpeed().y);
	Vector finalVector = Vector(finalPosition, getPosition().y);
	setPosition(finalVector);
}