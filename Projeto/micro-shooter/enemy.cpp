#include "enemy.hpp"

Enemy::Enemy()
{
	Vector position = Vector(400, 400);
	Vector speed = Vector(300, 300);
	this->setPosition(position);
	this->setSpeed(speed);
	this->setWidth(40.0);
	this->setHeight(40.0);
	this->setLife(3);
}

void Enemy::moveUp()
{
	float finalPosition = this->getPosition().y - (this->getSpeed().x * this->getSpeed().y);
	Vector finalVector = Vector(this->getPosition().x, finalPosition);
	this->setPosition(finalVector);
}

void Enemy::moveDown()
{
	float finalPosition = this->getPosition().y + (this->getSpeed().x * this->getSpeed().y);
	Vector finalVector = Vector(this->getPosition().x, finalPosition);
	this->setPosition(finalVector);
}

void Enemy::moveRight()
{
	float finalPosition = this->getPosition().x + (this->getSpeed().x * this->getSpeed().y);
	Vector finalVector = Vector(finalPosition, this->getPosition().y);
	this->setPosition(finalVector);
}

void Enemy::moveLeft()
{
	float finalPosition = this->getPosition().x - (this->getSpeed().x * this->getSpeed().y);
	Vector finalVector = Vector(finalPosition, this->getPosition().y);
	this->setPosition(finalVector);
}