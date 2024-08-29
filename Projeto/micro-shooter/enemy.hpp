#ifndef enemy_hpp
#define enemy_hpp

#include <iostream>
#include "object.hpp"
#include "graphic-implement-sdl.hpp"
#include "status-bar.hpp"

class Enemy : public Object {
private:
    int direction; // 1 para direita, -1 para esquerda
    bool dead;
    //StatusBar healthBar;

public:
    Enemy();
    void move(float frameTime) override;
    bool isDead() const; 
    void setDead(bool dead);
    void createHealthBar(GraphicImplementSdl* graphicInterface);
};

#endif