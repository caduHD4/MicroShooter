#ifndef enemy_hpp
#define enemy_hpp

#include <iostream>
#include "object.hpp"
#include "graphic-implement-sdl.hpp"
#include "status-bar.hpp"
#include "sprite.hpp"
#include <list>
#include "bullet.hpp"
#include <SDL_mixer.h>

class Enemy : public Object {
private:
    int direction; // 1 para direita, -1 para esquerda
    bool dead;
    int points;
    Uint32 lastShotTime = 0;
    Uint32 shotCooldown = 500;
    Mix_Chunk* shootEffect;
    std::list<Bullet*> bullets;

public:
    Enemy(SDL_Renderer* renderer);
    ~Enemy();
    void update(float deltaTime);
    void move(float frameTime) override;
    void updateHitbox();
    bool isDead() const; 
    void setDead(bool dead);
    void render(SDL_Renderer* renderer);
    void createHealthBar(GraphicImplementSdl* graphicInterface);
    void shootBullet(GraphicImplementSdl* graphicInterface, float frameTime);
    void shootBulletRemoteGuided(Object* player, GraphicImplementSdl* graphicInterface, float frameTime);
    void removeBullets();

    void setPoints(int points) {
        this->points = points;
    }

    int getPoints() {
        return this->points;
    }

    void setBullets(std::list<Bullet*> bullets) {
        this->bullets = bullets;
    }

    std::list<Bullet*> getBullets() {
        return this->bullets;
    }
};

#endif