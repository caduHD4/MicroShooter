#ifndef enemy_hpp
#define enemy_hpp

#include <iostream>
#include "object.hpp"
#include "graphic-implement-sdl.hpp"
#include "status-bar.hpp"
#include "sprite.hpp"


class Enemy : public Object {
private:
    int direction; // 1 para direita, -1 para esquerda
    bool dead;
    int points;

public:
    Enemy(SDL_Renderer* renderer);
    ~Enemy();
    void update(float deltaTime);
    void move(float frameTime) override;
    void updateHitbox();
    bool isDead() const; 
    void setDead(bool dead);
    void render(SDL_Renderer* renderer);
    void createHealthBar(GraphicImplementSdl* graphicInterface);

    void setPoints(int points) {
        this->points = points;
    }

    int getPoints() {
        return this->points;
    }
};

#endif