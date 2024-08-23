#ifndef player_hpp
#define player_hpp

#include <iostream>
#include "object.hpp"
#include "graphic-implement-sdl.hpp"
#include "sprite.hpp"

class Player : public Object
{
private:
    Sprite* sprite;

public:
    Player(SDL_Renderer* renderer);
    ~Player();
    void update(float deltaTime);
    void render(SDL_Renderer* renderer);
};

#endif