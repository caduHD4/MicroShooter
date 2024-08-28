#ifndef player_hpp
#define player_hpp

#include <iostream>
#include "object.hpp"
#include "graphic-implement-sdl.hpp"

class Player : public Object
{
private:
    const Uint8* keys;

public:
    Player(SDL_Renderer* renderer);
    ~Player();
    void update(float deltaTime);
    void render(SDL_Renderer* renderer);
};

#endif