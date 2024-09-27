#include "bullet.hpp"

Bullet::Bullet(Vector position, SDL_Renderer* renderer) {
    Vector speed = Vector(0, -1000);  // A velocidade é negativa para mover para cima
    this->setPosition(position);
    this->setSpeed(speed);
    this->setWidth(52);
    this->setHeight(60);
    this->setLife(1);

    sprite = new Sprite("sprite/mouse.png", renderer, 32, 32, 1, 0.1f);
}

Bullet::~Bullet() {
    delete sprite;
}

void Bullet::update(float deltaTime) {
    sprite->update(deltaTime);
    updateHitbox();
}


void Bullet::render(SDL_Renderer* renderer) {
    sprite->render(renderer, static_cast<int>(this->getPosition().x), static_cast<int>(this->getPosition().y), static_cast<int>(this->getWidth()), static_cast<int>(this->getHeight()));
    //renderHitbox(renderer);
}

void Bullet::updateHitbox() {
    hitbox.x = static_cast<int>(this->getPosition().x + 22);
    hitbox.y = static_cast<int>(this->getPosition().y +20);
    hitbox.w = static_cast<int>(10);
    hitbox.h = static_cast<int>(24);
}
