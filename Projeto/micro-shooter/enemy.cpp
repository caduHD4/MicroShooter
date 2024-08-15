#include "enemy.hpp"

Enemy::Enemy() : dead(false)
{
    Vector position = Vector(400, 400);
    Vector speed = Vector(300, 300);
    this->setPosition(position);
    this->setSpeed(speed);
    this->setWidth(40.0);
    this->setHeight(40.0);
    this->setLife(3);
    this->direction = 1;
}

bool Enemy::isDead() const {
    return dead;
}

void Enemy::setDead(bool dead) {
    this->dead = dead;
}

void Enemy::move(float frameTime) {
    // Movimento em zig-zag
    this->position.x += this->speed.x * frameTime * this->direction;

    // Verifica se o inimigo atingiu os limites da tela
    if (this->position.x <= 0 || this->position.x + this->width >= 720) {
        this->direction *= -1; // Inverte a direção
        this->position.x = std::max(0.0f, std::min(this->position.x, 720.0f - this->width));
    }

    // Movimento vertical constante
    this->position.y += this->speed.y * frameTime;
    if (this->position.y + this->height >= 200) {
        this->position.y = 200.0f - this->height; // Mantém dentro dos limites
    }
}

void Enemy::drawHealthBar(GraphicImplementSdl* graphicInterface) {
    float healthBarWidth = this->getWidth();
    float healthBarHeight = 5.0f;
    float healthPercentage = static_cast<float>(this->getLife()) / 3.0f;
    float currentHealthBarWidth = healthBarWidth * healthPercentage;

    if (currentHealthBarWidth > healthBarWidth) {
        currentHealthBarWidth = healthBarWidth;
    }

    Vector healthBarPosition = this->getPosition() + Vector(0, -10);

    Rect healthBarBackground = { healthBarPosition, healthBarWidth, healthBarHeight };
    Rect healthBarForeground = { healthBarPosition, currentHealthBarWidth, healthBarHeight };

    Color backgroundColor = { 255, 0, 0, 255 };
    Color foregroundColor = { 0, 255, 0, 255 }; 


    graphicInterface->drawRect(healthBarBackground, backgroundColor);
    graphicInterface->drawRect(healthBarForeground, foregroundColor);
}