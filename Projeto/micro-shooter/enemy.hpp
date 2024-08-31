#ifndef enemy_hpp
#define enemy_hpp

#include <iostream>
#include "object.hpp"
#include "graphic-implement-sdl.hpp"
#include "sprite.hpp"

class Enemy : public Object {
private:
    int direction; // 1 para direita, -1 para esquerda
    bool dead;

public:
    Enemy(SDL_Renderer* renderer);
    ~Enemy();
    void update(float deltaTime);
    void drawHealthBar(GraphicImplementSdl* graphicInterface);
    void move(float frameTime) override;
    bool isDead() const; 
    void setDead(bool dead);
    void render(SDL_Renderer* renderer);
};

#endif