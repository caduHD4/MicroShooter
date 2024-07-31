#ifndef player_hpp
#define player_hpp

#include <iostream>
#include "object.hpp"
#include "graphic-implement-sdl.hpp"

class Player : public Object
{
private:
    Rect rect;

public:
    Player();
    void move(float deltaX, float deltaY, float frameTime);
    Rect& getRect();
    void setRect(const Rect& rect);
};

#endif

