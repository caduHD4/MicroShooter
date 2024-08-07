
#ifndef game_hpp
#define game_hpp

#include <iostream>
#include <list>
#include "player.hpp"
#include "bullet.hpp"
#include "enemy.hpp"
#include "object.hpp"
#include "graphic-implement-sdl.hpp"
#include "event-implement-sdl.hpp"

class Game {
private:
    Player player;
    Enemy enemy;
    std::list<Bullet*> bullets;
    GraphicImplementSdl* graphicInterface;
    EventImplementSdl* eventInterface;
    const Uint8* keys;
    float FPS;
    float frameDelay;
    Uint32 frameStart;
    Uint32 frameTime;
    Uint32 lastShotTime;
    Uint32 shotCooldown = 100; // Cooldown entre tiros
    Vector enemyDirection;
    float enemySpeed;
    float enemyTime = 0.0f;

public:
    Game();
    void update(float deltaTime);
    void render();
    void shootBullet();
};

#endif