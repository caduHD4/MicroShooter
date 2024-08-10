#include "player.hpp"


Player::Player()
{
    Vector position = Vector(400, 400);
    Vector speed = Vector(500, 500);
    this->setPosition(position);
    this->setSpeed(speed);
    this->setWidth(40.0);
    this->setHeight(40.0);
    this->setLife(3);
}