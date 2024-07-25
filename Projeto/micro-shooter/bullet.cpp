#include "bullet.hpp"

Bullet::Bullet()
{
}
Bullet::Bullet(Vector position)
{
	Vector speed = Vector(12, 1);
	this->setPosition(position);
	this->setSpeed(speed);
	this->setWidth(40);
	this->setHeight(40);
	this->setLife(3);
}

void Bullet::moveUp()
{
	float finalPosition = this->getPosition().y - (this->getSpeed().x * this->getSpeed().y);
	Vector finalVector = Vector(this->getPosition().x, finalPosition);
	this->setPosition(finalVector);
}

void Bullet::moveDown()
{
	float finalPosition = this->getPosition().y + (this->getSpeed().x * this->getSpeed().y);
	Vector finalVector = Vector(this->getPosition().x, finalPosition);
	this->setPosition(finalVector);
}

void Bullet::moveRight()
{
	float finalPosition = this->getPosition().x + (this->getSpeed().x * this->getSpeed().y);
	Vector finalVector = Vector(finalPosition, this->getPosition().y);
	this->setPosition(finalVector);
}

void Bullet::moveLeft()
{
	float finalPosition = this->getPosition().x - (this->getSpeed().x * this->getSpeed().y);
	Vector finalVector = Vector(finalPosition, this->getPosition().y);
	this->setPosition(finalVector);
}
