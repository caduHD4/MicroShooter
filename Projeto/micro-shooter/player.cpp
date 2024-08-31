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

void Player::createHealthBar(GraphicImplementSdl* graphicInterface) {
    healthBar = StatusBar();
    healthBar.setWidth(300.0);
    healthBar.setHeight(20.0);
    healthBar.setBackgroundColor({ 255, 0, 0, 255 });
    healthBar.setForegroundColor({ 255, 255, 0, 255 });
    healthBar.setPosition(Vector(10, 10));
    healthBar.setPercentage(static_cast<float>(this->getLife()) / 3.0f);
    healthBar.drawStatusBar(graphicInterface);
}

void Player::createEnergyBar(GraphicImplementSdl* graphicInterface) {
    energyBar = StatusBar();
    energyBar.setWidth(300.0);
    energyBar.setHeight(20.0);
    energyBar.setBackgroundColor({ 255, 0, 0, 255 });
    energyBar.setForegroundColor({ 255, 69, 0, 255 });
    energyBar.setPosition(Vector(10, 40));
    energyBar.setPercentage(static_cast<float>(this->getLife()) / 3.0f);
    energyBar.drawStatusBar(graphicInterface);

bool Player::isDead() const {
    return dead;
}

void Player::setDead(bool dead) {
    this->dead = dead;
}