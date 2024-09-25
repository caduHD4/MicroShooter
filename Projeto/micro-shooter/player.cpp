#include "player.hpp"
#include "game.hpp"

Player::Player(SDL_Renderer* renderer) : dead(false)
{
    Vector position = Vector(400, 400);
    Vector speed = Vector(600, 600);
    this->setPosition(position);
    this->setSpeed(speed);
    this->setWidth(62.0);
    this->setHeight(70.0);
    this->setLife(3);

    sprite = new Sprite("sprite/playerJet.png", renderer, 32, 32, 6, 0.15f); // Ajuste de parametros do sprite, tamanho, velocidade e quantidade.
}

Player::~Player() {
    delete sprite;
}

void Player::update(float deltaTime) {
    sprite->update(deltaTime);
    updateHitbox();
}

void Player::render(SDL_Renderer* renderer) {
    sprite->render(renderer, static_cast<int>(this->getPosition().x), static_cast<int>(this->getPosition().y), static_cast<int>(this->getWidth()), static_cast<int>(this->getHeight()));
    renderHitbox(renderer);
}

void Player::createHealthBar(GraphicImplementSdl* graphicInterface) {
    healthBar = StatusBar(StatusBarInitialization{
        .width = 300.0, .backgroundColor = { 255, 0, 0, 255 }, .foregroundColor = { 255, 255, 0, 255 },
        .position = Vector(10, 10)
    });
    healthBar.setHeight(20.0);
    healthBar.setPercentage(static_cast<float>(this->getLife()) / 3.0f);
    healthBar.drawStatusBar(graphicInterface);
}

void Player::createEnergyBar(GraphicImplementSdl* graphicInterface) {
    energyBar = StatusBar(StatusBarInitialization{
        .width = 300.0, .backgroundColor = { 255, 0, 0, 255 }, .foregroundColor = { 255, 69, 0, 255 },
        .position = Vector(10, 40)
        });
    energyBar.setHeight(20.0);
    energyBar.setPercentage(static_cast<float>(this->getLife()) / 3.0f);
    energyBar.drawStatusBar(graphicInterface);
}

bool Player::isDead() const {
    return dead;
}

void Player::setDead(bool dead) {
    this->dead = dead;
}

void Player::limiteTela(float frameTime) {
    //Colis�o com limite da tela, necess�rio refatorar!!
    if (this->position.x + this->width >= 1920) {
        this->moveLeft(frameTime);
    }
    if (this->position.x <= 0) {
        this->moveRight(frameTime);
    }
    if (this->position.y <= 0) {
        this->moveDown(frameTime);
    }
    if (this->position.y + this->width >= 1080) {
        this->moveUp(frameTime);
    }
}
    
void Player::updateHitbox() {
    hitbox.x = static_cast<int>(this->getPosition().x);
    hitbox.y = static_cast<int>(this->getPosition().y);
    hitbox.w = static_cast<int>(62);
    hitbox.h = static_cast<int>(70);
}

void Player::shootBullet(GraphicImplementSdl* graphicInterface, float frameTime) {
    Uint32 currentTime = SDL_GetTicks();
    // cooldown entre tiros
    if (currentTime - lastShotTime >= shotCooldown) {
        Vector playerPos = this->getPosition();
        Vector bulletSpeed = Vector(0, -0.9f);
        Bullet* newBullet = new Bullet(playerPos + Vector(this->getWidth() / 4, -30), graphicInterface->getSdlRenderer(), bulletSpeed);
        int channel = Mix_PlayChannel(-1, shootEffect, 0);
        bullets.push_back(newBullet);
        lastShotTime = currentTime; // Atualiza o tempo do último disparo
    }
}

void Player::bulletCollision(Enemy* enemy, Mix_Chunk* enemyDestroyedEffect) {
    for (auto bullet : bullets) {
        if (SDL_HasIntersection(&bullet->getHitbox(), &enemy->getHitbox())) {
            std::cout << "Colisao com a bala!" << std::endl;
            enemy->setLife(enemy->getLife() - 1);
            if (enemy->getLife() <= 0) {
                std::cout << "Inimigo destruido!" << std::endl;
                this->updateScore(enemy->getPoints());
                std::cout << "Pontuacao: " << this->getScore() << std::endl;
                int channel = Mix_PlayChannel(-1, enemyDestroyedEffect, 0);
                enemy->setDead(true);
            }
            bullet->setLife(0);
        }
    }
}

void Player::removeBullets() {
    auto bulletRemover = [](Bullet* b) -> bool {
        if (b->getPosition().y < 0 || b->getLife() <= 0) {
            delete b;
            return true;
        }
        return false;
    };
    bullets.remove_if(bulletRemover);
}