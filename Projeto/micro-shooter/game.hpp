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
#include "SDL_mixer.h"

class Game {
private:
    Player* player;
    std::list<Enemy*> enemies;
    std::list<Bullet*> bullets;
    GraphicImplementSdl* graphicInterface;
    EventImplementSdl* eventInterface;
    const Uint8* keys;
    float FPS;
    float frameDelay;
    Uint32 frameStart;
    Uint32 frameTime;
    Uint32 lastShotTime;
    Uint32 lastSpawnTime;
    Uint32 shotCooldown = 100;
    Uint32 enemiesCooldown = 150;
    Vector enemyDirection;
    float enemySpeed;
    float enemyTime = 0.0f;
    Mix_Chunk* shootEffect;
    Mix_Chunk* enemyDestroyedEffect;
    bool isFrozen;

public:
    Game();
    ~Game();
    void update(float deltaTime);
    void render();
    void shootBullet();
    void spawnEnemies();
    void showGameOverScreen();
    void showScore();
};

#endif