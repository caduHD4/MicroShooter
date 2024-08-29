#include "bullet.hpp"

Bullet::Bullet(Vector position) {
    Vector speed = Vector(0, -1000);  // A velocidade é negativa para mover para cima
    this->setPosition(position);
    this->setSpeed(speed);
    this->setWidth(12);
    this->setHeight(12);
    this->setLife(1);
}