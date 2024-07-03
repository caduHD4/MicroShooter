#include "player.hpp"

Player::Player()
{
	Vector position = Vector(400, 400);
	Vector speed = Vector(300, 300);
	this->setPosition(position);
	this->setSpeed(speed);
	this->setWidth(40.0);
	this->setHeight(40.0);
	this->setLife(3);
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