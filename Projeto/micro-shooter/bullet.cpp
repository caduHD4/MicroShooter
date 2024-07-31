#include "bullet.hpp"

Bullet::Bullet() {}

Bullet::Bullet(Vector position) {
    Vector speed = Vector(0, -1000);  // A velocidade é negativa para mover para cima
    this->setPosition(position);
    this->setSpeed(speed);
    this->setWidth(12);
    this->setHeight(12);
    this->setLife(1);
}

// Ajuste o método para mover com base no frameTime e na velocidade da bala
void Bullet::move(float frameTime) {
    // Chame o método move da classe base Object com a velocidade da bala
    Object::move(0.0f, 1.0f, frameTime);  // Move para cima usando a velocidade
}
