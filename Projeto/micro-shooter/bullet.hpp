#ifndef bullet_hpp
#define bullet_hpp

#include <stdio.h>
#include <iostream>
#include "SDL.h"
#include "object.hpp"

class Bullet : public Object {
public:
    Bullet(Vector position, SDL_Renderer* renderer);
    ~Bullet();
    void update(float deltaTime);
    void render(SDL_Renderer* renderer);
    void updateHitbox();
};

#endif
