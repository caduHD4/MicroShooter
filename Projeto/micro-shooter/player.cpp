#include "player.hpp"

Player::Player(SDL_Renderer* renderer)
{
    Vector position = Vector(400, 400);
    Vector speed = Vector(600, 600);
    this->setPosition(position);
    this->setSpeed(speed);
    this->setWidth(40.0);
    this->setHeight(40.0);
    this->setLife(3);

    sprite = new Sprite("sprite/PlayerSprite.png", renderer, 40, 40, 4, 0.1f); // Ajuste os parâmetros conforme necessário
}

Player::~Player() {
    delete sprite;
}

void Player::update(float deltaTime) {
    sprite->update(deltaTime);
}

void Player::render(SDL_Renderer* renderer) {
    sprite->render(renderer, static_cast<int>(this->getPosition().x), static_cast<int>(this->getPosition().y));
}