#ifndef player_hpp
#define player_hpp

#include <iostream>
#include "object.hpp"
#include "graphic-implement-sdl.hpp"
#include "status-bar.hpp"

class Player : public Object
{
private:
    const Uint8* keys;
    StatusBar healthBar;
    StatusBar energyBar;
    bool dead;
    int score;

public:
    Player(SDL_Renderer* renderer);
    ~Player();
    void update(float deltaTime);
    void render(SDL_Renderer* renderer);
    void createHealthBar(GraphicImplementSdl* graphicInterface);
    void createEnergyBar(GraphicImplementSdl* graphicInterface);
    bool isDead() const;
    void setDead(bool dead);
    void limiteTela(float frameTime);
    
    void setScore(int score) {
        this->score = score;
    }

    int getScore() {
        return this->score;
    }

    void updateScore(int points) {
        this->score += points;
    }
};

#endif