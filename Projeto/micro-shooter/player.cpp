#include "player.hpp"


Player::Player()
{
	// Posição inicial do jogador, tamanho, vida e velocidade
    Vector position = Vector(400, 400);
    Vector speed = Vector(600, 600);
    this->setPosition(position);
    this->setSpeed(speed);
    this->setWidth(40.0);
    this->setHeight(40.0);
    this->setLife(3);
}

// Remover métodos moveUp, moveDown, etc.
void Player::move(float deltaX, float deltaY, float frameTime) {
    Object::move(deltaX, deltaY, frameTime);
}

