#include "player.hpp"
#include "game.hpp"

Player::Player(SDL_Renderer* renderer) : dead(false)
{
    Vector position = Vector(400, 400);
    Vector speed = Vector(600, 600);
    this->setPosition(position);
    this->setSpeed(speed);
    this->setWidth(52.0);
    this->setHeight(60.0);
    this->setLife(3);

    sprite = new Sprite("sprite/PlayerSprite.png", renderer, 32, 32, 6, 0.15f); // Ajuste de parametros do sprite, tamanho, velocidade e quantidade.
}

Player::~Player() {
    delete sprite;
}

void Player::update(float deltaTime) {
    sprite->update(deltaTime);
}

void Player::render(SDL_Renderer* renderer) {
    sprite->render(renderer, static_cast<int>(this->getPosition().x), static_cast<int>(this->getPosition().y), static_cast<int>(this->getWidth()), static_cast<int>(this->getHeight()));
}

bool Player::isDead() const {
    return dead;
}

void Player::setDead(bool dead) {
    this->dead = dead;
}