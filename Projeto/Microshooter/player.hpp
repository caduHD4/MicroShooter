#ifndef player_hpp
#define player_hpp

#include <iostream>
#include "object.hpp"
#include "graphic-implement-sdl.hpp"
#include "status-bar.hpp"
#include <list>
#include "bullet.hpp"
#include <SDL_mixer.h>
#include "enemy.hpp"

class Player : public Object
{
private:
    const Uint8* keys;
    StatusBar healthBar;
    StatusBar energyBar;
    bool dead;
    int score;
    bool isBlinking;
    float blinkTime;
    float blinkDuration = 1.0f; // Duração de cada piscar
    int blinkCount;
    Uint32 lastShotTime = 0;
    Uint32 shotCooldown = 100;
    Mix_Chunk* shootEffect;
    std::list<Bullet*> bullets;

public:
    Player(SDL_Renderer* renderer);
    ~Player();
    void update(float deltaTime);
    void render(SDL_Renderer* renderer);
    void createHealthBar(GraphicImplementSdl* graphicInterface);
    void createEnergyBar(GraphicImplementSdl* graphicInterface);
    bool isDead() const;
    void setDead(bool dead);
    void limiteTela(float frameTime);
    void updateHitbox();
    void takeDamage(int damage);
    bool getIsBlinking() const;
    void shootBullet(GraphicImplementSdl* graphicInterface, float frameTime);
    void bulletCollision(Enemy* enemy, Mix_Chunk* enemyDestroyedEffect);
    void removeBullets();

    void setScore(int score) {
        this->score = score;
    }

    int getScore() {
        return this->score;
    }

    void updateScore(int points) {
        this->score += points;
    }

    void setBullets(std::list<Bullet*> bullets) {
        this->bullets = bullets;
    }

    std::list<Bullet*> getBullets() {
        return this->bullets;
    }
};

#endif