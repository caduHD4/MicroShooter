#ifndef enemy_hpp
#define enemy_hpp

#include <iostream>
#include "object.hpp"
#include "graphic-implement-sdl.hpp"

class Enemy : public Object {
public:
    Enemy();
    void drawHealthBar(GraphicImplementSdl* graphicInterface);
};

#endif