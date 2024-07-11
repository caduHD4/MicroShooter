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
    float newY = this->position.y - getSpeed().y * frameTime;
    // Limitar ao topo da janela
    if (newY >= 0) {
        this->position.y = newY;
    }
}

void Player::moveDown(float frameTime)
{
    float newY = this->position.y + getSpeed().y * frameTime;
    // Limitar à parte inferior da janela
    if (newY <= (720 - this->getHeight())) {
        this->position.y = newY;
    }
}

void Player::moveRight(float frameTime)
{
    float newX = this->position.x + getSpeed().x * frameTime;
    // Limitar ao lado direito da janela
    if (newX <= (720 - this->getWidth())) {
        this->position.x = newX;
    }
}

void Player::moveLeft(float frameTime)
{
    float newX = this->position.x - getSpeed().x * frameTime;
    // Limitar ao lado esquerdo da janela
    if (newX >= 0) {
        this->position.x = newX;
    }
}
