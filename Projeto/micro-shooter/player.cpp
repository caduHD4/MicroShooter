#include "player.hpp"

Player::Player()
{
	// Posi��o inicial do jogador, tamanho, vida e velocidade
    Vector position = Vector(400, 400);
    Vector speed = Vector(400, 400);
    this->setPosition(position);
    this->setSpeed(speed);
    this->setWidth(40.0);
    this->setHeight(40.0);
    this->setLife(3);
}

void Player::moveUp(float frameTime)
{
    float newY = this->position.y - getSpeed().y * frameTime;
    // Limita ao topo da janela
    if (newY >= 0) {
        this->position.y = newY;
    }
}

void Player::moveDown(float frameTime)
{
    float newY = this->position.y + getSpeed().y * frameTime;
    // Limita � parte inferior da janela
    if (newY <= (720 - this->getHeight())) {
        this->position.y = newY;
    }
}

void Player::moveRight(float frameTime)
{
    float newX = this->position.x + getSpeed().x * frameTime;
    // Limita ao lado direito da janela
    if (newX <= (720 - this->getWidth())) {
        this->position.x = newX;
    }
}

void Player::moveLeft(float frameTime)
{
    float newX = this->position.x - getSpeed().x * frameTime;
    // Limita ao lado esquerdo da janela
    if (newX >= 0) {
        this->position.x = newX;
    }
}
