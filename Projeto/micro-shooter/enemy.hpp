#ifndef enemy_hpp
#define enemy_hpp

#include <iostream>
#include "object.hpp"
#include "graphic-implement-sdl.hpp"

class Enemy : public Object {
private:
    int direction; // 1 para direita, -1 para esquerda
    bool dead;

public:
    Enemy();
    void drawHealthBar(GraphicImplementSdl* graphicInterface);
    void move(float frameTime) override;
    bool isDead() const; 
    void setDead(bool dead);
};

#endif