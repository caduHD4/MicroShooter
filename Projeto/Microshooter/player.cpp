#include "player.hpp"
#include "game.hpp"

Player::Player(SDL_Renderer* renderer) : dead(false), isBlinking(false), blinkTime(0.0f), blinkCount(0) 
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
    if (sprite != nullptr) {
        delete sprite;
        sprite = nullptr;
    }
    if (shootEffect != nullptr) {
        Mix_FreeChunk(shootEffect);
        shootEffect = nullptr;
    }
}

void Player::takeDamage(int damage) {
    if (isBlinking) {
        return;
    }
    this->setLife(this->getLife() - damage);
    if (this->getLife() <= 0) {
        this->setDead(true);
    }
    isBlinking = true;

}

void Player::update(float deltaTime) {
    sprite->update(deltaTime);
    updateHitbox();
    if (isBlinking) {
        blinkTime += deltaTime;
        if (blinkTime >= blinkDuration) {
            blinkTime = 0.0f;
            blinkCount++;
            if (blinkCount >= 1) { // 5 segundos, piscando 2 vezes por segundo
                isBlinking = false;
                blinkCount = 0;
            }
        }
    }
}

void Player::render(SDL_Renderer* renderer) {
    if (sprite == nullptr) {
        return;
    }
    if (isBlinking && static_cast<int>(blinkTime * 10) % 2 == 0) {
        sprite->render(renderer, static_cast<int>(this->getPosition().x), static_cast<int>(this->getPosition().y), static_cast<int>(this->getWidth()), static_cast<int>(this->getHeight()), {255, 0, 0, 255});
    } else {
        sprite->render(renderer, static_cast<int>(this->getPosition().x), static_cast<int>(this->getPosition().y), static_cast<int>(this->getWidth()), static_cast<int>(this->getHeight()));
    }
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
    hitbox.x = static_cast<int>(this->getPosition().x + 10);
    hitbox.y = static_cast<int>(this->getPosition().y);
    hitbox.w = static_cast<int>(this->getWidth() - 20);
    hitbox.h = static_cast<int>(this->getHeight());
}

bool Player::getIsBlinking() const {
    return isBlinking;
}

void Player::shootBullet(GraphicImplementSdl* graphicInterface, float frameTime) {
    Uint32 currentTime = SDL_GetTicks();
    // cooldown entre tiros
    if (currentTime - lastShotTime >= shotCooldown) {
        Vector playerPos = this->getPosition();
        Vector bulletSpeed = Vector(0, -0.9f);
        Bullet* newBullet = new Bullet(playerPos + Vector(this->getWidth() / 4, -30), graphicInterface->getSdlRenderer(), bulletSpeed);
        
        // Comentar a linha atual que toca o som
        // int channel = Mix_PlayChannel(-1, shootEffect, 0);
        
        // Nova abordagem para tocar o som do disparo
int channel = Mix_PlayChannel(-1, shootEffect, 0);
if (channel == -1) {
    std::cerr << "Failed to play sound effect: " << Mix_GetError() << std::endl;
}


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
                //int channel = Mix_PlayChannel(-1, enemyDestroyedEffect, 0);
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