#include "enemy.hpp"

Enemy::Enemy(SDL_Renderer* renderer) : dead(false)
{
    Vector position = Vector(400, 400);
    Vector speed = Vector(300, 300);
    this->setPoints(5);
    this->setPosition(position);
    this->setSpeed(speed);
    this->setWidth(102.0);
    this->setHeight(110.0);
    this->setLife(3);
    this->direction = 1;

    sprite = new Sprite("sprite/enemySprite.png", renderer, 32, 32, 4, 0.15f);
}

Enemy::~Enemy() {
    delete sprite;
}

void Enemy::update(float deltaTime) {
    sprite->update(deltaTime);
    updateHitbox();
}


void Enemy::render(SDL_Renderer* renderer) {
    sprite->render(renderer, static_cast<int>(this->getPosition().x), static_cast<int>(this->getPosition().y), static_cast<int>(this->getWidth()), static_cast<int>(this->getHeight()));
    //renderHitbox(renderer);
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
    if (this->position.x <= 0 || this->position.x + this->width >= 1920) {
        this->direction *= -1; // Inverte a dire��o
        this->position.x = std::max(0.0f, std::min(this->position.x, 1920.0f - this->width));
    }

    // Movimento vertical constante
    this->position.y += this->speed.y * frameTime;
    if (this->position.y + this->height >= 200) {
        this->position.y = 200.0f - this->height; // Mant�m dentro dos limites
    }
}

void Enemy::createHealthBar(GraphicImplementSdl* graphicInterface) {
    
    StatusBar healthBar = StatusBar(StatusBarInitialization{
        .width = 80.0, .backgroundColor = { 255, 0, 0, 255 }, .foregroundColor = { 0, 255, 0, 255 },
        .position = this->getPosition() + Vector(0, -10)
    });
    healthBar.setPercentage(static_cast<float>(this->getLife()) / 3.0f);
    healthBar.drawStatusBar(graphicInterface);

}

void Enemy::updateHitbox() {
	hitbox.x = static_cast<int>(this->getPosition().x +25);
	hitbox.y = static_cast<int>(this->getPosition().y +25);
	hitbox.w = static_cast<int>(60);
	hitbox.h = static_cast<int>(50);
}

void Enemy::shootBullet(GraphicImplementSdl* graphicInterface, float frameTime) {
    Uint32 currentTime = SDL_GetTicks();
    // cooldown entre tiros
    if (currentTime - lastShotTime >= shotCooldown) {
        Vector playerPos = this->getPosition();
        Vector bulletSpeed = Vector(0, 0.9f);
        Bullet* newBullet = new Bullet(playerPos + Vector(this->getWidth() / 4, -30), graphicInterface->getSdlRenderer(), bulletSpeed);
        int channel = Mix_PlayChannel(-1, shootEffect, 0);
        bullets.push_back(newBullet);
        lastShotTime = currentTime; // Atualiza o tempo do �ltimo disparo
    }
}

void Enemy::removeBullets() {
    auto bulletRemover = [](Bullet* b) -> bool {
        if (b->getPosition().y > 1080 || b->getLife() <= 0) {
            delete b;
            return true;
        }
        return false;
        };
    bullets.remove_if(bulletRemover);
}

void Enemy::shootBulletRemoteGuided(Object* player, GraphicImplementSdl* graphicInterface, float frameTime) {
    Uint32 currentTime = SDL_GetTicks();
    // cooldown entre tiros
    if (currentTime - lastShotTime >= shotCooldown) {
        Vector enemyPos = this->getPosition();
        Vector bulletSpeed = player->getPosition() - enemyPos;
        bulletSpeed.set_length(0.5f);
        Bullet* newBullet = new Bullet(enemyPos + Vector(this->getWidth() / 4, -30), graphicInterface->getSdlRenderer(), bulletSpeed);
        newBullet->setIsRemoteGuided(true);
        int channel = Mix_PlayChannel(-1, shootEffect, 0);
        bullets.push_back(newBullet);
        lastShotTime = currentTime; // Atualiza o tempo do �ltimo disparo
    }
}