#include "enemy.hpp"

Enemy::Enemy() 
{
    Vector position = Vector(400, 400);
    Vector speed = Vector(300, 300);
    this->setPosition(position);
    this->setSpeed(speed);
    this->setWidth(40.0);
    this->setHeight(40.0);
    this->setLife(20);
}

void Enemy::drawHealthBar(GraphicImplementSdl* graphicInterface) {
    float healthBarWidth = this->getWidth();
    float healthBarHeight = 5.0f;
    float healthPercentage = static_cast<float>(this->getLife()) / 20.0f;
    float currentHealthBarWidth = healthBarWidth * healthPercentage;

    // Garantir que a largura da barra de vida atual não exceda a largura máxima
    if (currentHealthBarWidth > healthBarWidth) {
        currentHealthBarWidth = healthBarWidth;
    }

    Rect healthBarBackground = { this->getPosition() + Vector(0, -10), healthBarWidth, healthBarHeight };
    Rect healthBarForeground = { this->getPosition() + Vector(0, -10), currentHealthBarWidth, healthBarHeight };

    Color backgroundColor = { 255, 0, 0, 255 }; // Vermelho para o fundo
    Color foregroundColor = { 0, 255, 0, 255 }; // Verde para a vida atual

    graphicInterface->drawRect(healthBarBackground, backgroundColor);
    graphicInterface->drawRect(healthBarForeground, foregroundColor);
}