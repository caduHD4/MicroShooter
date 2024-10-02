#ifndef bullet_hpp
#define bullet_hpp

#include <stdio.h>
#include <iostream>
#include "SDL.h"
#include "object.hpp"

class Bullet : public Object {

private:
    bool isRemoteGuided = false;

public:
    Bullet(Vector position, SDL_Renderer* renderer, Vector speed);
    ~Bullet();
    void update(float deltaTime);
    void render(SDL_Renderer* renderer);
    void updateHitbox();
    void moveRemoteGuided(Object* player, float frameTime);

    bool getIsRemoteGuided() {
        return this->isRemoteGuided;
    }

    void setIsRemoteGuided(bool isRemoteGuided) {
        this->isRemoteGuided = isRemoteGuided;
    }
};

#endif
